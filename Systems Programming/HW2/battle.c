#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "status.h"

typedef struct {
	// 1: left child process, 2: right child process
	char type1, type2; // b: battle, p: player
	char id1[4], id2[4];
	Attribute attribute;
} Battle_type;

Battle_type battle_dict[14] = {
	[0] = {.type1 = 'b', .type2 = 'b', .id1 = "B", .id2 = "C", .attribute = FIRE},    // battle A
	[1] = {.type1 = 'b', .type2 = 'b', .id1 = "D", .id2 = "E", .attribute = GRASS},   // battle B
	[2] = {.type1 = 'b', .type2 = 'p', .id1 = "F", .id2 = "14", .attribute = WATER},  // battle C
	[3] = {.type1 = 'b', .type2 = 'b', .id1 = "G", .id2 = "H", .attribute = WATER},   // battle D
	[4] = {.type1 = 'b', .type2 = 'b', .id1 = "I", .id2 = "J", .attribute = FIRE},    // battle E
	[5] = {.type1 = 'b', .type2 = 'b', .id1 = "K", .id2 = "L", .attribute = FIRE},    // battle F
	[6] = {.type1 = 'p', .type2 = 'p', .id1 = "0", .id2 = "1", .attribute = FIRE},    // battle G
	[7] = {.type1 = 'p', .type2 = 'p', .id1 = "2", .id2 = "3", .attribute = GRASS},   // battle H
	[8] = {.type1 = 'p', .type2 = 'p', .id1 = "4", .id2 = "5", .attribute = WATER},   // battle I
	[9] = {.type1 = 'p', .type2 = 'p', .id1 = "6", .id2 = "7", .attribute = GRASS},   // battle J
	[10] = {.type1 = 'b', .type2 = 'p', .id1 = "M", .id2 = "10", .attribute = GRASS}, // battle K
	[11] = {.type1 = 'b', .type2 = 'p', .id1 = "N", .id2 = "13", .attribute = GRASS}, // battle L
	[12] = {.type1 = 'p', .type2 = 'p', .id1 = "8", .id2 = "9", .attribute = FIRE},   // battle M
	[13] = {.type1 = 'p', .type2 = 'p', .id1 = "11", .id2 = "12", .attribute = WATER} // battle N
};

char parent_battle[14] = {'\0', 'A', 'A', 'B', 'B', 'C', 'D', 'D', 'E', 'E', 'F', 'F', 'K', 'L'};

int stat;

int main(int argc, char *argv[]){
	pid_t process_id = getpid();
	char battle_id = argv[1][0];
	long parent_id = atol(argv[2]);
	Battle_type battle_type = battle_dict[battle_id - 'A'];

	setvbuf(stdout, NULL, _IONBF, 0);

	// init mode
	// Step 1
	char logfile_name[16];
	sprintf(logfile_name, "log_battle%c.txt", battle_id);
	FILE* fp_log = fopen(logfile_name, "w+");
	setvbuf(fp_log, NULL, _IONBF, 0);

	// Step 2 - pipe
	int pipe_fd1[2][2]; // parent process writes to child process
	int pipe_fd2[2][2]; // child process writes to parent process

	pipe(pipe_fd1[0]);
	pipe(pipe_fd2[0]);
		
	// Step 2 - fork
	pid_t child_pid1, child_pid2;
	if ((child_pid1 = fork()) == 0){
		// left child process
		close(pipe_fd1[0][1]);
		dup2(pipe_fd1[0][0], STDIN_FILENO);
		close(pipe_fd1[0][0]);

		close(pipe_fd2[0][0]);
		dup2(pipe_fd2[0][1], STDOUT_FILENO);
		close(pipe_fd2[0][1]);

		// exec
		char process_id_str[16];
		if (battle_type.type1 == 'b'){
			memset(process_id_str, 0, 16);
			sprintf(process_id_str, "%ld", (long) process_id);
			execl("./battle", "battle", battle_type.id1, process_id_str, NULL);
		}

		else if (battle_type.type1 == 'p'){
			memset(process_id_str, 0, 16);
			sprintf(process_id_str, "%ld", (long) process_id);
			execl("./player", "player", battle_type.id1, process_id_str, NULL);
		}
		
	}
	else{
		close(pipe_fd1[0][0]);
		close(pipe_fd2[0][1]);

		pipe(pipe_fd1[1]);
		pipe(pipe_fd2[1]);
			
		if ((child_pid2 = fork()) == 0){
			// child process 2
			close(pipe_fd1[1][1]);
			dup2(pipe_fd1[1][0], STDIN_FILENO);
			close(pipe_fd1[1][0]);

			close(pipe_fd2[1][0]);
			dup2(pipe_fd2[1][1], STDOUT_FILENO);
			close(pipe_fd2[1][1]);

			// exec
			char process_id_str[16];
			if (battle_type.type2 == 'b'){
				memset(process_id_str, 0, 16);
				sprintf(process_id_str, "%ld", (long) process_id);
				execl("./battle", "battle", battle_type.id2, process_id_str, NULL);
			}

			else if (battle_type.type2 == 'p'){
				memset(process_id_str, 0, 16);
				sprintf(process_id_str, "%ld", (long) process_id);
				execl("./player", "player", battle_type.id2, process_id_str, NULL);
			}
		}
		else{
			// parent process
			close(pipe_fd1[1][0]);
			close(pipe_fd2[1][1]);

			// waiting mode
			FILE* fp_1r = fdopen(pipe_fd2[0][0], "r");
			FILE* fp_1w = fdopen(pipe_fd1[0][1], "w");
			setvbuf(fp_1w, NULL, _IONBF, 0);

			FILE* fp_2r = fdopen(pipe_fd2[1][0], "r");
			FILE* fp_2w = fdopen(pipe_fd1[1][1], "w");
			setvbuf(fp_2w, NULL, _IONBF, 0);

			// playing mode
			// step 3
			int battle_end = 0;
			int remain_process; // 1: left child process, 2: right child_process
			int winner_id;
			while (!battle_end){
				// step 3
				Status player1_status, player2_status;

				fread(&player1_status, sizeof(Status), 1, fp_1r);
				fprintf(fp_log, "%c,%ld pipe from %s,%ld %d,%d,%c,%d\n", 
					battle_id, (long) process_id, battle_type.id1, (long) child_pid1, 
					player1_status.real_player_id, player1_status.HP, player1_status.current_battle_id, player1_status.battle_ended_flag);

				fread(&player2_status, sizeof(Status), 1, fp_2r);
				fprintf(fp_log, "%c,%ld pipe from %s,%ld %d,%d,%c,%d\n", 
					battle_id, (long) process_id, battle_type.id2, (long) child_pid2, 
					player2_status.real_player_id, player2_status.HP, player2_status.current_battle_id, player2_status.battle_ended_flag);

				// step 4
				player1_status.current_battle_id = battle_id;
				player2_status.current_battle_id = battle_id;
				if (player1_status.HP < player2_status.HP || (player1_status.HP == player2_status.HP && player1_status.real_player_id < player2_status.real_player_id)){
					// player1 attacks first
					if (player1_status.attr == battle_type.attribute) // ATK double
						player2_status.HP -= player1_status.ATK * 2;
					else
						player2_status.HP -= player1_status.ATK;
					
					if (player2_status.HP <= 0){ // player2 die
						remain_process = 1;
						battle_end = 1;
					}
						
					else{
						if (player2_status.attr == battle_type.attribute) // ATK double
							player1_status.HP -= player2_status.ATK * 2;
						else
							player1_status.HP -= player2_status.ATK;
						
						if (player1_status.HP <= 0){ // player1 die
							remain_process = 2;
							battle_end = 1;
						}
					}
				}

				else{
					// player2 attacks first
					if (player2_status.attr == battle_type.attribute) // ATK double
						player1_status.HP -= player2_status.ATK * 2;
					else
						player1_status.HP -= player2_status.ATK;
						
					if (player1_status.HP <= 0){ // player1 die
						remain_process = 2;
						battle_end = 1;
					}
					else{
						if (player1_status.attr == battle_type.attribute) // ATK double
							player2_status.HP -= player1_status.ATK * 2;
						else
							player2_status.HP -= player1_status.ATK;
						
						if (player2_status.HP <= 0){ // player2 die
							remain_process = 1;
							battle_end = 1;
						}
					}
				}

				if (battle_end){
					player1_status.battle_ended_flag = 1;
					player2_status.battle_ended_flag = 1;

					if (battle_id == 'A'){
						if (remain_process == 1)
							winner_id = player1_status.real_player_id;
						else if (remain_process == 2)
							winner_id = player2_status.real_player_id;
					}
				}

				// step 5
				fprintf(fp_log, "%c,%ld pipe to %s,%ld %d,%d,%c,%d\n", 
					battle_id, (long) process_id, battle_type.id1, (long) child_pid1, 
					player1_status.real_player_id, player1_status.HP, player1_status.current_battle_id, player1_status.battle_ended_flag);
				fwrite(&player1_status, sizeof(Status), 1, fp_1w);

				fprintf(fp_log, "%c,%ld pipe to %s,%ld %d,%d,%c,%d\n", 
					battle_id, (long) process_id, battle_type.id2, (long) child_pid2, 
					player2_status.real_player_id, player2_status.HP, player2_status.current_battle_id, player2_status.battle_ended_flag);
				fwrite(&player2_status, sizeof(Status), 1, fp_2w);
			}

			if (battle_id == 'A'){
				waitpid(child_pid1, &stat, 0);
				waitpid(child_pid2, &stat, 0);

				printf("Champion is P%d\n", winner_id);
			}

			else{
				// passing mode
				// step 6
				int process_end = 0;
				while (!process_end){
					Status player_status;
					if (remain_process == 1){
						waitpid(child_pid2, &stat, 0);

						fread(&player_status, sizeof(Status), 1, fp_1r);
						fprintf(fp_log, "%c,%ld pipe from %s,%ld %d,%d,%c,%d\n", 
							battle_id, (long) process_id, battle_type.id1, (long) child_pid1, 
							player_status.real_player_id, player_status.HP, player_status.current_battle_id, player_status.battle_ended_flag);

						fprintf(fp_log, "%c,%ld pipe to %c,%ld %d,%d,%c,%d\n", 
							battle_id, (long) process_id, parent_battle[battle_id - 'A'], parent_id, 
							player_status.real_player_id, player_status.HP, player_status.current_battle_id, player_status.battle_ended_flag);
						fwrite(&player_status, sizeof(Status), 1, stdout);

						fread(&player_status, sizeof(Status), 1, stdin);
						fprintf(fp_log, "%c,%ld pipe from %c,%ld %d,%d,%c,%d\n", 
							battle_id, (long) process_id, parent_battle[battle_id - 'A'], parent_id, 
							player_status.real_player_id, player_status.HP, player_status.current_battle_id, player_status.battle_ended_flag);
				
						fprintf(fp_log, "%c,%ld pipe to %s,%ld %d,%d,%c,%d\n", 
							battle_id, (long) process_id, battle_type.id1, (long) child_pid1, 
							player_status.real_player_id, player_status.HP, player_status.current_battle_id, player_status.battle_ended_flag);
						fwrite(&player_status, sizeof(Status), 1, fp_1w);

						if (player_status.battle_ended_flag == 1){
							if (player_status.HP <= 0 || player_status.current_battle_id == 'A'){
								process_end = 1;
								waitpid(child_pid1, &stat, 0);
							}
						}		
					}
						
					else if (remain_process == 2){
						waitpid(child_pid1, &stat, 0);
						
						fread(&player_status, sizeof(Status), 1, fp_2r);
						fprintf(fp_log, "%c,%ld pipe from %s,%ld %d,%d,%c,%d\n", 
							battle_id, (long) process_id, battle_type.id2, (long) child_pid2, 
							player_status.real_player_id, player_status.HP, player_status.current_battle_id, player_status.battle_ended_flag);

						fprintf(fp_log, "%c,%ld pipe to %c,%ld %d,%d,%c,%d\n", 
							battle_id, (long) process_id, parent_battle[battle_id - 'A'], parent_id, 
							player_status.real_player_id, player_status.HP, player_status.current_battle_id, player_status.battle_ended_flag);
						fwrite(&player_status, sizeof(Status), 1, stdout);

						fread(&player_status, sizeof(Status), 1, stdin);
						fprintf(fp_log, "%c,%ld pipe from %c,%ld %d,%d,%c,%d\n", 
							battle_id, (long) process_id, parent_battle[battle_id - 'A'], parent_id, 
							player_status.real_player_id, player_status.HP, player_status.current_battle_id, player_status.battle_ended_flag);

						fprintf(fp_log, "%c,%ld pipe to %s,%ld %d,%d,%c,%d\n", 
							battle_id, (long) process_id, battle_type.id2, (long) child_pid2, 
							player_status.real_player_id, player_status.HP, player_status.current_battle_id, player_status.battle_ended_flag);
						fwrite(&player_status, sizeof(Status), 1, fp_2w);

						if (player_status.battle_ended_flag == 1){
							if (player_status.HP <= 0 || player_status.current_battle_id == 'A'){
								process_end = 1;
								waitpid(child_pid2, &stat, 0);
							}
						}
					}
				}
			}
		}	
	}
	return 0;
}