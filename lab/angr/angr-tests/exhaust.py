#!/usr/bin/env python

import angr
import time
import sys

def main():
    if len(sys.argv) < 2:
        print 'argument missing. give a binary to test.'
        return

    p = angr.Project(sys.argv[1])

    state = p.factory.entry_state() # address of entry point
    path = p.factory.path(state) # initial path from entry point
    pg = p.factory.path_group(path) # pathgroup from entry point

    e = p.surveyors.Explorer(max_repeats=1000)

    while e.done == False:
        e.run(100)
        print time.time(),' ',e
    print 'done'

    for i in range(0,len(e.deadended)):
        print 'deadend ',i,': ',e.deadended[i]
        try:
            print 'in -> ', e.deadended[i].state.posix.dumps(0)
        except:
            print 'no input generated'
        try:
            print 'out -> ',e.deadended[i].state.posix.dumps(1)
        except:
            print 'no output generated'

def test(): pass

if __name__ == '__main__':
    main()
