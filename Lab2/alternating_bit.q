//This file was generated from UPPAAL 4.0.6 (rev. 2987), March 2007

/*

*/
S.s1 --> S.s0

/*

*/
S.s0 --> (R.wait0 or R.wait1)

/*

*/
E<> S.timeout1

/*

*/
E<> S.timeout0

/*

*/
A[] not deadlock
