/******************************************************

Module: Printing out some statistics of an IC3 run
        (Part 1)

Author: Eugene Goldberg, eu.goldberg@gmail.com

******************************************************/
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include "minisat/core/Solver.h"
#include "minisat/simp/SimpSolver.h"
#include "dnf_io.hh"
#include "ccircuit.hh"
#include "m0ic3.hh"


/*==============================

  P R I N T _ S T A T

  =============================*/
void CompInfo::print_stat()
{

  printf("num of time frames = %d\n",max_num_tfs);
  if (inv_ind >= 0)   printf("inv_ind = %d\n",inv_ind);
  my_printf("#inputs = %m, #outputs = %m, #latches = %m, #gates = %m\n",
	    N->ninputs,N->noutputs,N->nlatches, N->ngates);
  printf("total number of generated clauses is %d\n",(int) F.size()- 
         (int) Ist.size() + init_ind_cls());


  my_printf("orig_ind_cls = %m, succ_impr = %m, failed_impr = %m\n",
            orig_ind_cls,succ_impr,failed_impr);
  

  // print the total average size

  printf("Aver. clause size = %.1f\n",average());

  printf("max. num. improv. of an ind. clause is %d\n",max_num_impr);
  my_printf("#add1 = %m, #add2 = %m, #replaced = %m, #restore = %m\n",
            num_add1_cases,num_add2_cases,num_replaced_cases,num_restore_cases);
  print_sat_stat();

  print_flags();

  printf("muliplier = %.2f\n",multiplier);

  print_lifting_stat();
  my_printf("root_state_cnt = %m, new_state_cnt = %m, old_state_cnt = %m",
            root_state_cnt,new_state_cnt,old_state_cnt);
  my_printf(" (triv = %m, rem = %m)\n",triv_old_st_cnt,
            old_state_cnt-triv_old_st_cnt);

 
  my_printf("#CTGs = %m, #excluded CTGS = %m\n",tot_ctg_cnt,succ_ctg_cnt);
} /* end of function print_stat */


/*============================

  A V E R A G E

  ==========================*/
float CompInfo::average()
{

  float total = 0.;
  for (size_t i=Ist.size(); i < F.size(); i++) {
    total += F[i].size();
  }

  int num_clauses = F.size()-Ist.size();
  if (num_clauses > 0)  return(total * 1. / num_clauses);
  else return(0.);
} /* end of function average */


/*========================================

  P R I N T _ S A T _ S T A T

  =========================================*/
void CompInfo::print_sat_stat(){

  print_one_sat_stat(Gen_sat);
  print_one_sat_stat(Bst_sat);
  print_one_sat_stat(Lbs_sat);
  print_one_sat_stat(Lgs_sat);

  int time_frame_calls;
  print_time_frame_sat_stat(time_frame_calls);

  print_all_calls(time_frame_calls);

} /* end of function print_one_sat_stat */

/*=============================================

  P R I N T _ O N E _ S A T _ S T A T

  =============================================*/
void CompInfo::print_one_sat_stat(SatSolver &S)
{

  if (Name_table.find(S.Name) == Name_table.end()) 
    return;

  std::cout << S.Name << ": ";
  printf("%d calls\n",S.tot_num_calls);

} /* end of function print_one_sat_stat */


/*========================================

  P R I N T _ T I M E _ F R A M E _ S T A T

  ========================================*/
void CompInfo::print_time_frame_stat()
{

  if (verbose > 0) {
    printf("------------------\n");
    printf("finished time frame number %d\n",(int) Time_frames.size()-1);
  }

  TimeFrame &Tf = Time_frames[tf_lind];
  if (verbose > 0) 
    printf("new derived clauses Bnd[%d]=%d, Bnd[%d]=%d\n",tf_lind,
           Tf.num_bnd_cls,tf_lind+1,
	   Time_frames[tf_lind+1].num_bnd_cls);


  if (verbose > 0)  {
    printf("num_pbs-s: %d\n",Tf.num_pbss);

    printf("Cti-s:\n");
    int count = 0;
    for (int i=tf_lind; i >=0; i--) {
      if (Time_frames[i].num_rcnt_ctis == 0) continue;
      if (count++ > 0) printf(", ");    
      printf("Tf[%d] = %d",i,Time_frames[i].num_rcnt_ctis);
      if (count % 10 == 0) printf("\n"); 
    }

    if (verbose > 0)
      if (count % 10 != 0)  printf("\n");
  }
 
  int time_frame_calls;
  if (verbose > -1) print_time_frame_sat_stat(time_frame_calls);

  if (verbose > 0) 
    my_printf("F.size() = %m, num. inact. clauses  = %m\n",(int) F.size(), 
              num_inact_cls);
  //  printf("num. seen (redund) cls = %d (%d)\n",Tf.num_seen_cls,
  // Tf.num_redund_cls);
} /* end of function print_time_frame_stat*/


/*===================================================

  P R I N T _ T I M E _ F R A M E _ S A T _ S T A T

  ==================================================*/
void CompInfo::print_time_frame_sat_stat(int &time_frame_calls)
{

  time_frame_calls = 0;

  for (size_t i=0; i < Time_frames.size(); i++) 
    time_frame_calls += Time_frames[i].Slvr.num_calls;

  my_printf("Time frame SAT-solvers: %m calls\n",time_frame_calls); 
  my_printf("Push clause SAT-solving: %m calls\n",num_push_clause_calls);

} /* end of function print_time_frame_sat_stat */

/*=================================================

  P R I N T _ A L L _ C A L L S

  ==================================================*/
void CompInfo::print_all_calls(int time_frame_calls)
{

  int all_calls = time_frame_calls;
  if (Name_table.find(Gen_sat.Name) != Name_table.end()) 
    all_calls += Gen_sat.tot_num_calls;

  if (Name_table.find(Bst_sat.Name) != Name_table.end()) 
    all_calls += Bst_sat.tot_num_calls;

  if (Name_table.find(Lbs_sat.Name) != Name_table.end()) 
    all_calls += Lbs_sat.tot_num_calls;

  if (Name_table.find(Lgs_sat.Name) != Name_table.end()) 
    all_calls += Lgs_sat.tot_num_calls;



  my_printf("all solvers: %m calls\n",all_calls);

} /* end of function print_all_calls */



