//discuss with b06303131 ¨H®aºÍ

#include "ADA_HW4_3.h"

using namespace std;

vector<int> contest;
vector<int> pos_to_id;
vector<int> del_pair(3000); // id to id
vector<bool> in_contest(3000); // id to in

vector<int> init(int N){
    int i;
    for (i = 0; i < N; i++)
        pos_to_id.push_back(i);
    int l = 0;
    int r = 1;
    bool found;
    while (r < N){
        if (compare(l, r) == false){
            found = false;
            contest.push_back(l);
            contest.push_back(r);
            in_contest[l] = true;
            in_contest[r] = true;
            del_pair[l] = r;
            del_pair[r] = l;
            r++;
            for (i = (l - 1); i >= 0; i--){
                if (in_contest[i] == false){
                    l = i;
                    found = true;
                    break;
                }
            }
            if (found == false){
                l = r;
                r++;
            }
        }
        else{
            l = r;
            r++;
        }
    }
    return contest;
}

vector<int> insert(int p, int id){
    pos_to_id.insert(pos_to_id.begin() + p, id);
    int i;
    bool found = 0;
    for (i = (p - 1); i >= 0; i--){
        if (in_contest[pos_to_id[i]] == false){
            if (compare(pos_to_id[i], id) == false){
                contest.push_back(pos_to_id[i]);
                contest.push_back(id);
                in_contest[pos_to_id[i]] = true;
                in_contest[id] = true;
                del_pair[pos_to_id[i]] = id;
                del_pair[id] = pos_to_id[i];
                found = true;
            }
            break;
        }
    }
    if (found == false){
        for (i = (p + 1); i < pos_to_id.size(); i++){
            if (in_contest[pos_to_id[i]] == false){
                if (compare(id, pos_to_id[i]) == false){
                    contest.push_back(pos_to_id[i]);
                    contest.push_back(id);
                    in_contest[pos_to_id[i]] = true;
                    in_contest[id] = true;
                    del_pair[pos_to_id[i]] = id;
                    del_pair[id] = pos_to_id[i];
                }
                break;
            }
        }
    }
    return contest;
}

vector<int> remove(int p){
    if (in_contest[pos_to_id[p]] == true){
        int i, pos;
        int id = del_pair[pos_to_id[p]];
        for (i = 0; i < pos_to_id.size(); i++){
            if (pos_to_id[i] == id){
                pos = i;
                break;
            }
        }
        bool found = false;
        for (i = (pos - 1); i >= 0; i--){
            if (in_contest[pos_to_id[i]] == false){
                if (compare(pos_to_id[i], id) == false){
                    contest.push_back(pos_to_id[i]);
                    in_contest[pos_to_id[i]] = true;
                    del_pair[pos_to_id[i]] = id;
                    del_pair[id] = pos_to_id[i];
                    found = true;
                }
                break;
            }
        }
        if (found == false){
            for (i = (pos + 1); i < pos_to_id.size(); i++){
                if (in_contest[pos_to_id[i]] == false){
                    if (compare(id, pos_to_id[i]) == false){
                        contest.push_back(pos_to_id[i]);
                        in_contest[pos_to_id[i]] = true;
                        del_pair[pos_to_id[i]] = id;
                        del_pair[id] = pos_to_id[i];
                        found = true;
                    }
                    break;
                }
            }
        }
        for (i = 0; i < contest.size(); i++){
            if (contest[i] == pos_to_id[p]){
                contest.erase(contest.begin() + i);
                break;
            }
        }
        if (found == false){
            for (i = 0; i < contest.size(); i++){
                if (contest[i] == id){
                    contest.erase(contest.begin() + i);
                    break;
                }
            }
            in_contest[id] = false;
        }
        in_contest[pos_to_id[p]] = false;
    }
    pos_to_id.erase(pos_to_id.begin() + p);
    return contest;
}
