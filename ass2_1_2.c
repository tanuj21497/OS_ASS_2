#include<stdio.h>

#include<unistd.h>

#include<wait.h>

#include<time.h>

#include<sched.h>

#include<errno.h>

















int main(){

    // int errno;

    long int time_initial_nsec =0;

    long int time_initial_sec =0;

    long int time_1_nsec=0;

    long int time_2_nsec=0;

    long int time_1_sec=0;

    long int time_2_sec=0;

    long int time_3_nsec=0;

    long int time_3_sec=0;

    pid_t process_1=-1;

    pid_t process_2=-1;

    pid_t process_3=-1;

    struct timespec time_initial;

    struct timespec time_1;

    struct timespec time_2;

    struct timespec time_3;



    if(clock_gettime(CLOCK_REALTIME, &time_initial)==0){

        time_initial_nsec = time_initial.tv_nsec;

        time_initial_sec  = time_initial.tv_sec;



    }

    else{

        perror("ERROR: ");

        return 0;

    }

    if(process_1 =fork() == 0){

        struct sched_param p1;

        p1.sched_priority = 3;

        if(sched_setscheduler(getpid(), SCHED_RR, &p1)!=0){

            perror("ERROR: ");

            return 0;

        }

        execl("./new.sh", "./new.sh", NULL);

    }

    else{



       

        

        if(clock_gettime(CLOCK_REALTIME, &time_1)==0){

            time_1_nsec = time_1.tv_nsec;

            time_1_sec = time_1.tv_sec;



        }

        else{

            perror("ERROR: ");

            return 0;

        }



        pid_t pid2 ;

        if(pid2 = fork() == 0){

            struct sched_param p2;

            p2.sched_priority = 2;

            if(sched_setscheduler(getpid(), SCHED_FIFO, &p2)!=0){

                perror("ERROR: ");

                return 0;

            }

            execl("./new.sh", "./new.sh", NULL);

        }

        else{

            if(clock_gettime(CLOCK_REALTIME, &time_2)==0){

                time_2_nsec = time_2.tv_nsec;

                time_2_sec = time_2.tv_sec;



            }

            else{

                perror("ERROR: ");

                return 0;

            }

        

             

            if(process_3 = fork() == 0){



                struct sched_param p3;

                p3.sched_priority = 0;   

                if(sched_setscheduler(getpid(), SCHED_OTHER, &p3)!=0){

                    perror("ERROR: ");

                    return 0;

                }

                execl("./new.sh", "./new.sh",NULL);

            }

            else{

                while(waitpid(-1, NULL, 0) > 0){





                    

                    if(clock_gettime(CLOCK_REALTIME, &time_3)==0){

                        time_3_nsec = time_3.tv_nsec;

                        time_3_sec = time_3.tv_sec;



                    }

                    else{

                        perror("ERROR: ");



                        return 0;

                    }

                }



                



                printf("\nFor process1: %f \nFor process2: %f \nFor process3: %f\n", (time_3_sec - time_initial_sec + (time_3_nsec - time_initial_nsec)/1e9), (time_3_sec - time_1_sec + (time_3_nsec - time_1_nsec)/1e9), (time_3_sec - time_2_sec + (time_3_nsec - time_2_nsec)/1e9));

            }

        }

    }



    return 0;



}