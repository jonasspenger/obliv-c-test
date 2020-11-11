import sys
import os
import random
import logging

commands = {"set": 1, "get": 2, "remove": 3, "clear": 5, "prune": 4}

class Benchmark():
    def __init__(self, n=1000):
        self.n = int(n)
        self.kvs = [None] * self.n
        for i in range(self.n):
            k = random.randint(0, self.n)
            v = random.randint(0, self.n)
            self.kvs[i] = (k, v)

    def start(self):
        logging.info("starting benchmark")

        # set #n k,v pairs randomly sampled from [0, n)
        for (k, v) in self.kvs:
            sys.stdout.write("%d %d %d " % (commands["set"], k, v))
        sys.stdout.flush()

        random.shuffle(self.kvs)

        # get #n k,v pairs randomly sampled from [0, n)
        for (k, v) in self.kvs:
            sys.stdout.write("%d %d %d " % (commands["get"], k, v))
        sys.stdout.flush()

        random.shuffle(self.kvs)

        # remove #n k,v pairs randomly sampled from [0, n)
        for (k, v) in self.kvs:
            sys.stdout.write("%d %d %d " % (commands["remove"], k, v))

        # prune state
        sys.stdout.write("%d %d %d " % (commands["prune"], 0, 0))
        sys.stdout.flush()

        # set #n k,v pairs randomly sampled from [0, n)
        for (k, v) in self.kvs:
            sys.stdout.write("%d %d %d " % (commands["set"], k, v))
        sys.stdout.flush()

        # clear state
        sys.stdout.write("%d %d %d " % (commands["clear"], 0, 0))
        sys.stdout.flush()

        sys.stdout.flush()
        sys.stdout.write("\n")

if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", default="1000", help="number of sets followed by deletes")
    args = parser.parse_args()
    logging.getLogger().setLevel("INFO")
    benchmark = Benchmark(n=args.n)
    benchmark.start()
