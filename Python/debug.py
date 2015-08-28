u"""
An script to allow setting breakpoints as:
    # breakpoint [cond]
    cond = if condition
And transforming those to:
    [if cond:] pdb.set_trace()
Injects 'import pdb' and it's NOT safe at all!
    # breakpoint if exec(print('hacked'))
        ->
    if exec(print('hacked')): pdb.set_trace()
Use it with care!
USAGE:
    python script file_to_debug
    (or import it and launch the run method)
"""
# TODO: 
# 1. Refinar el pattern de la condicio
# 2. Securitzar l'evaluacio del if
import re, sys

class Debugger(object):
    DEBUG = True
    PY3 = sys.version[0] == u'3'
    EXPR = re.compile(
            r'(?P<indent>{sep}*)#{sep}*breakpoint{sep}*(?P<cond>if .+|){sep}*$'\
            .format(sep=u'[ \t]'), re.IGNORECASE)

    def __init__(self, filename):
        super(Debugger, self).__init__()
        self.filename = filename

    @classmethod
    def _match(cls, line):
        m = cls.EXPR.match(line)
        if m:
            lif = m.group(u'cond')
            lif = lif + u': ' if lif else u''
            line = u'%s%spdb.set_trace()\n' % (m.group(u'indent'), lif)
        return line

    def _compile(self, flags=0, dont_inherit=False, optimize=-1):
        with open(self.filename, u'r') as fb:
            res = [self._match(line) for line in fb.readlines()]

        if self.DEBUG:
            with open(self.filename, u'r') as fb:
                print(u''.join(fb.readlines()))
            print(u''.join(res))

        kwargs = {'flags': flags, 'dont_inherit': dont_inherit}

        if self.PY3:
            kwargs['optimize'] = optimize

        return compile(source=u''.join(res), filename=self.filename, mode=u'exec',
                **kwargs)

    def run(self):
        # src of this part:
        #   https://hg.python.org/cpython/file/3.4/Lib/pdb.py
        # The script has to run in __main__ namespace (or imports from
        # __main__ will break).
        #
        # So we clear up the __main__ and set several special variables
        import __main__
        builtins = __main__.__dict__['__builtins__']
        __main__.__dict__.clear()
        __main__.__dict__.update({"__name__"    : "__main__",
                                  "__file__"    : self.filename,
                                  "__builtins__": builtins,
                                 })
        import pdb
        exec(self._compile(), {u'pdb': pdb})


if __name__ == u'__main__' and len(sys.argv) == 2:
    Debugger(filename=sys.argv[1]).run()
