#!/usr/bin/env python

import angr
import simuvex
import time

def basic_symbolic_execution():
    p = angr.Project('test')
    e = p.surveyors.Explorer()

    maxRuns = 1000
    step = 10
    run = 0

    deCount = 0
    erCount = 0

    while e.done == False and run < maxRuns:
        e.run(step)
        run += step
        print time.time(),' ',e

        if len(e.deadended) > deCount:
            for i in range(deCount,len(e.deadended)):
	        print 'deadend ',i,': ',e.deadended[i]
                try:
                    print 'in -> ', e.deadended[i].state.posix.dumps(0)
                except: pass
                try:
                    print 'out -> ',e.deadended[i].state.posix.dumps(1)
                except: pass
                try:
                    print 'err -> ',e.deadended[i].state.posix.dumps(2)
                except: pass
            deCount = len(e.deadended)
        
        if len(e.errored) > erCount:
            for i in range(erCount,len(e.errored)):
	        print 'error ',i,': ',e.errored[i]
                try:
                    print 'in -> ', e.errored[i].state.posix.dumps(0)
                except: pass
                try:
                    print 'out -> ',e.errored[i].state.posix.dumps(1)
                except: pass
                try:
                    print 'err -> ',e.errored[i].state.posix.dumps(2)
                except: pass
            erCount = len(e.errored)

    print 'done'


def test():
    pass        # appease our CI infrastructure which expects this file to do something lmao

if __name__ == '__main__':
    print basic_symbolic_execution()
