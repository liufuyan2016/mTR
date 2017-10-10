//
//  print_one_repeat.c
//  
//
//  Created by Shinichi Morishita on 2017/10/06.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "mTR.h"

int feed_rr_into_repeats_in_all_reads(char *inputFile){
    FILE *fp = fopen(inputFile, "r");
    if(fp == NULL){
        fprintf(stderr, "fatal error: cannot open %s\n", inputFile);
        exit(EXIT_FAILURE);
    }
    char s[BLK];
    int i = 0;

    
    while( fscanf(fp, "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
             &repeats_in_all_reads[i].ID,
             repeats_in_all_reads[i].readID,
             &repeats_in_all_reads[i].inputLen,
             &repeats_in_all_reads[i].max_start,
             &repeats_in_all_reads[i].max_end,
             &repeats_in_all_reads[i].actual_repeat_len,
             &repeats_in_all_reads[i].rep_period,
             &repeats_in_all_reads[i].actual_rep_period,
             &repeats_in_all_reads[i].Num_freq_unit,
             &repeats_in_all_reads[i].Num_matches,
             &repeats_in_all_reads[i].Num_mismatches,
             &repeats_in_all_reads[i].Num_insertions,
             &repeats_in_all_reads[i].Num_deletions,
             &repeats_in_all_reads[i].Kmer,
             &repeats_in_all_reads[i].ConsensusMethod,
             repeats_in_all_reads[i].string,
             &repeats_in_all_reads[i].freq_2mer[0], &repeats_in_all_reads[i].freq_2mer[1],
             &repeats_in_all_reads[i].freq_2mer[2], &repeats_in_all_reads[i].freq_2mer[3],
             &repeats_in_all_reads[i].freq_2mer[4], &repeats_in_all_reads[i].freq_2mer[5],
             &repeats_in_all_reads[i].freq_2mer[6], &repeats_in_all_reads[i].freq_2mer[7],
             &repeats_in_all_reads[i].freq_2mer[8], &repeats_in_all_reads[i].freq_2mer[9],
             &repeats_in_all_reads[i].freq_2mer[10],&repeats_in_all_reads[i].freq_2mer[11],
             &repeats_in_all_reads[i].freq_2mer[12],&repeats_in_all_reads[i].freq_2mer[13],
             &repeats_in_all_reads[i].freq_2mer[14],&repeats_in_all_reads[i].freq_2mer[15]
                  ) != EOF )
    {
        //pretty_print_one_repeat_in_read(repeats_in_all_reads[i]);
        i++;
    }
    
    fclose(fp);
    return(i);
}

void print_one_repeat_in_read(repeat_in_read rr){
    char message[1000] = "";
    sprintf(message, "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s",
            rr.ID,
            rr.readID,
            rr.inputLen,
            rr.max_start,
            rr.max_end,
            rr.actual_repeat_len,
            rr.rep_period,
            rr.actual_rep_period,
            rr.Num_freq_unit,
            rr.Num_matches,
            rr.Num_mismatches,
            rr.Num_insertions,
            rr.Num_deletions,
            rr.Kmer,
            rr.ConsensusMethod,
            rr.string
            );
    char tmp_msg[6]="";
    for(int i=0; i<16; i++){
        sprintf(tmp_msg, "\t%d", rr.freq_2mer[i]);
        strcat(message, tmp_msg);
    }
    printf("%s\n", message);
}


void pretty_print_one_repeat_in_read(repeat_in_read rr){
    
    char message[1000] = "";
    char consensus[100];
    if(rr.ConsensusMethod == 0){
        strcpy(consensus, "Progressive MA ");
    }else{
        strcpy(consensus, "De Bruijn graph");
    }
    
    if(rr.actual_rep_period > 0){
        sprintf(message, "ID = %i,\treadID = %s,\tREAD_length = %i,\tREPEAT_start = %i,\tend = %i,\tlen(act) = %i,\tUNIT_len(est) = %i,\tlen(act) = %i,\t#Units = %i,\tMatches = %i,\tMismacthes = %i,\tIns = %i,\tDel = %i,\tKmer = %i,\tMethod = %s,\tUnit_string= %s,\t2mer_freq = ",
                rr.ID,
                rr.readID,
                rr.inputLen,
                rr.max_start,
                rr.max_end,
                rr.actual_repeat_len,
                rr.rep_period,
                rr.actual_rep_period,
                rr.Num_freq_unit,
                rr.Num_matches,
                rr.Num_mismatches,
                rr.Num_insertions,
                rr.Num_deletions,
                rr.Kmer,
                consensus,
                rr.string
                );
        char tmp_msg[6]="";
        for(int i=0; i<16; i++){
            sprintf(tmp_msg, "%i,", rr.freq_2mer[i]);
            strcat(message, tmp_msg);
        }
    }else{
        sprintf(message, "ID = %i,\treadID = %s,\tREAD_length = %i,\tREPEAT_start = %i,\tend = %i,\tlen(est) = %i,\tlen(act) = NA,\t\tUNIT len(est) = %i,\tlen(act) = NA for Kmer = %i",
                rr.ID,
                rr.readID,
                rr.inputLen,
                rr.max_start,
                rr.max_end,
                (rr.max_end - rr.max_start + 1),
                rr.rep_period,
                rr.Kmer
                );
    }
    printf("%s\n", message);
}
