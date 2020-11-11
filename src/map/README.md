# Oblivious Map
Implementation of an oblivious map using Obliv-c framework.

## Setup
* Install: `make`
* Run: `echo -e "1 1 1 1 1 2 1 2 2 2 1 1 3 2 0 4 0 0 5 0 0 1 1 1" | ./a.out 1 localhost 3897 & echo -e "1 3 3 1 3 4 1 4 4 2 3 3 3 4 0 4 0 0 5 0 0 1 2 2" | ./a.out 2 localhost 3897;`
* Help: `./a.out -h`
* Benchmark: `time python workload.py -n 20 | ./a.out 1 localhost 3897 & python workload.py -n 20 | ./a.out 2 localhost 3897`

## Algorithm MPC Stateful Function
* function statefulmap: state, input -> state, output;  // takes encrypted state and inputs from 2 parties and generates new encrypted state and output  
* function statefulmap': rvar, state, input -> rvar, state, output;
  * state = rvar_p_1 ^ rvar_p_2 ^ state  // decrypt state using rvar from p1 and p2
  * state, output = statefulmap(state, input)
  * rvar_p_1, rvar_p_2 = generate random variables
  * state = rvar_p_1 ^ rvar_p_2 ^ state
  * return rvar, state, output
* initialize state;
* initialize rvar;  // random variable
* upon input do
  * ygc = new instance of Yao's garbled circuit of function statefulmap'
  * rvar, state, output = ygc.evaluate(rvar, state, input)  // this is secure
  * trigger output to client

## Correctness
* Assumption: implementation of Yao's garbled circuit is correct, i.e. secure function evaluation for 2 parties
* Execution of ygc publicly reveals: encrypted state and the output.
* To show: the adversary does not gain any more information from the pair <encrypted state, output> than compared to <output>
* Because encrypted_state = state ^ rvar_p_1 ^ rvar_p_2, the probability that any algorithm A could reconstruct the state from the encrypted state from the pair, <encrypted_state, rvar_p_1> is P_A[A(<encrypted_state, rvar_p_1, output>) = state] =  P_A[A(<encrypted_state, rvar_p_2, output>) = state] = 1 / |RV| (informally as good as guessing) (if rvar chosen uniformly from RV) = P_A[A(<output>)].
