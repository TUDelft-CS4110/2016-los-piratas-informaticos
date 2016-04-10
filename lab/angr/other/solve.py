#!/usr/bin/env python

import angr
import simuvex
import time

def basic_symbolic_execution():
    load_options = {}
    load_options['auto_load_libs'] = True
    load_options['force_load_libs'] = ['libpng16.so']
    p = angr.Project('STR/main')

    print 'shared objects ',p.loader.shared_objects


#    p.loader.shared_objects['libc.so.6'].imports
    print p.loader.shared_objects

    lpng = simuvex.SimProcedures['libc.so.6']
    print lpng

    state = p.factory.entry_state() # address of entry point
    path = p.factory.path(state) # initial path from entry point
    pg = p.factory.path_group(path) # pathgroup from entry point

    e = p.surveyors.Explorer()

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

def test():
    pass        # appease our CI infrastructure which expects this file to do something lmao

if __name__ == '__main__':
    print basic_symbolic_execution()
