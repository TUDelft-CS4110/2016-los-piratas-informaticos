import angr
import simuvex
import time

def main():
    load_options = {
        'auto_load_libs': False,
        'skip_libs': 'libc.so.6'
    }
    p = angr.Project('main', load_options=load_options)

    print p.loader.shared_objects
    print p.entry
    print p.loader

    path = p.factory.path()
    print path
    path = path.step()
    print path[0]
    while len(path) == 1:
        path = path[0].step()
        print path[0]

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
    main()
