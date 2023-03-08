//This file was generated from UPPAAL 4.0.6 (rev. 2987), March 2007

/*
Fischer's mutual exclusion protocol.
*/
//NO_QUERY

/*
Mutex requirement.
*/
A[] not ( ( P1.cs and ( P2.cs or P3.cs or P4.cs or P5.cs or P6.cs or P7.cs or P8.cs or P9.cs) ) or \
          ( P2.cs and ( P3.cs or P4.cs or P5.cs or P6.cs or P7.cs or P8.cs or P9.cs) ) or \
          ( P3.cs and ( P4.cs or P5.cs or P6.cs or P7.cs or P8.cs or P9.cs) ) or\
          ( P4.cs and ( P5.cs or P6.cs or P7.cs or P8.cs or P9.cs) ) or\
          ( P5.cs and ( P6.cs or P7.cs or P8.cs or P9.cs) ) or\
          ( P6.cs and ( P7.cs or P8.cs or P9.cs) ) or\
          ( P7.cs and (P8.cs or P9.cs) ) or\
          ( P8.cs and P9.cs )\
        )

/*
The system is deadlock free.
*/
A[] not deadlock

/*
Whenever P1 requests access to the critical section it will eventually enter the wait state.
*/
P1.req --> P1.wait

/*

*/
//NO_QUERY
