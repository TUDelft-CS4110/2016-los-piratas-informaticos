#!/usr/bin/env python

import angr
import simuvex

def main():
    p = angr.Project('normalread') # adjusted version of normalread

    state = p.factory.blank_state(remove_options={simuvex.s_options.LAZY_SOLVES})

    image_name = "test.png"

    content = simuvex.SimSymbolicMemory(memory_id="file_%s" % image_name)
    content.set_state(state)
    
    #storing content in the simulated file can decrease number of paths and constraint solving time
    #f = open('test.png', 'r')
    #content.store(0, f.read())

    image_file = simuvex.SimFile(image_name, 'rw', size=255, content=content)

    state.posix.fs = {image_name: image_file} # set state filesystem

    path = p.factory.path(state=state)
    ex = p.surveyors.Explorer(start=path)
    
    deCount = 0

    while len(ex.active) > 0:
	ex.run(10)
        print ex
	if len(ex.deadended) > deCount:
            for x in range(deCount,len(ex.deadended)):
                try:
		    print ex.deadended[x].state.posix.dumps(1) # dump the std output
                except: pass
                try:
                    print ex.deadended[x].state.posix.dumps(2) # dump the std err
                except: pass
            deCount = len(ex.deadended)

def test(): pass
if __name__ == '__main__':
    main()

