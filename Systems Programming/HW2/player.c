#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "status.h"

char battle_id[15] = {'G', 'G', 'H', 'H', 'I', 'I', 'J', 'J', 'M', 'M', 'K', 'N', 'N', 'L', 'C'};
int real_to_agent[10] = {-1, 14, -1, 10, 13, -1, 8, 11, 9, 12};
int initial_HP[8];

int main(int argc, char *argv[]){
	pid_t process_id = getpid();
	int player_id = atoi(argv[1]);
	long parent_id = atol(argv[2]);
	FILE* fp_log;

	setvbuf(stdout, NULL, _IONBF, 0);

	FILE* fp_init = fopen("player_status.txt", "r");

	for (int i = 0; i < 8; i++)
		fscanf(fp_init, "%d %*d %*s %*c %*d\n", &(initial_HP[i]));

	// Step 1
	Status player_status;

	if (player_id >= 0 && player_id <= 7){
		rewind(fp_init);
		char buf[32];
		for (int i = 0; i < player_id; i++)
			fscanf(fp_init, "%*d %*d %*s %*c %*d\n");
		
		char attr_str[8];
		fscanf(fp_init, "%d %d %s %c %d\n", &(player_status.HP), &(player_status.ATK), attr_str, &(player_status.current_battle_id), &(player_status.battle_ended_flag));
		player_status.real_player_id = player_id;
		if (attr_str[0] == 'F')
			player_status.attr = FIRE;
		else if (attr_str[0] == 'G')
			player_status.attr = GRASS;
		else if (attr_str[0] == 'W')
			player_status.attr = WATER;

		char logfile_name[16];
		sprintf(logfile_name, "log_player%d.txt", player_id);
		fp_log = fopen(logfile_name, "w+");
		setvbuf(fp_log, NULL, _IONBF, 0);
	}
	else if (player_id >= 8 && player_id <= 14){
		char FIFO_name[16];
		sprintf(FIFO_name, "player%d.fifo", player_id);
		mkfifo(FIFO_name, 0666);
		FILE *fp_r = fopen(FIFO_name, "r");

		fread(&player_status, sizeof(Status), 1, fp_r);

		char logfile_name[16];
		sprintf(logfile_name, "log_player%d.txt", player_status.real_player_id);
		fp_log = fopen(logfile_name, "a+");
		setvbuf(fp_log, NULL, _IONBF, 0);

		fprintf(fp_log, "%d,%ld fifo from %d %d,%d\n", 
			player_id, (long) process_id, 
			player_status.real_player_id, player_status.real_player_id, player_status.HP);
	}

	int losed = 0;
	while (!losed){
		// Step 2
		fprintf(fp_log, "%d,%ld pipe to %c,%ld %d,%d,%c,%d\n", 
			player_id, (long) process_id, battle_id[player_id], parent_id, 
			player_status.real_player_id, player_status.HP, player_status.current_battle_id, player_status.battle_ended_flag);
		fwrite(&player_status, sizeof(Status), 1, stdout);

		// Step 3
		fread(&player_status, sizeof(Status), 1, stdin);
		fprintf(fp_log, "%d,%ld pipe from %c,%ld %d,%d,%c,%d\n", 
			player_id, (long) process_id, battle_id[player_id], parent_id, 
			player_status.real_player_id, player_status.HP, player_status.current_battle_id, player_status.battle_ended_flag);

		if (player_status.battle_ended_flag == 1){
			if (player_status.current_battle_id == 'A')
				break;
			else{
				if (player_status.HP > 0){ // winner
					player_status.HP += (initial_HP[player_status.real_player_id] - player_status.HP) / 2;
					player_status.battle_ended_flag = 0;
				}
				else{ // loser
					losed = 1;
					if (player_id == player_status.real_player_id){ // real player
						player_status.HP = initial_HP[player_id];
						player_status.battle_ended_flag = 0;

						fprintf(fp_log, "%d,%ld fifo to %d %d,%d\n", 
							player_id, (long) process_id, 
							real_to_agent[player_status.current_battle_id - 'A'], player_status.real_player_id, player_status.HP);

						char FIFO_name[16];
						sprintf(FIFO_name, "player%d.fifo", real_to_agent[player_status.current_battle_id - 'A']);
						FILE* fp_w = fopen(FIFO_name, "w");
						setvbuf(fp_w, NULL, _IONBF, 0);

						fwrite(&player_status, sizeof(Status), 1, fp_w);
					}
				}
			}
		}
	}
	return 0;
}