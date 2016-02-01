import itertools
import sys
from collections import namedtuple


class GetoptError(Exception):
    msg = ''

    def __init__(self, msg):
        self.msg = msg
        Exception.__init__(self, msg)

OptionTypeMandatory = namedtuple('OptionTypeMandatory', ['type', 'mandatory'])


class AvailableOptions():

    def __init__(self):
        self.options = {}

    def parse_argv(self, args):
        # Inits
        opts = []

        opt_name = ''
        opt_val = ''

        # Add fictive '--' to push last option tuple in loop
        args.append('--')

        # Process args
        for arg_str in args:

            if arg_str.startswith('--'):

                # Push previous
                if opt_name:

                    if opt_val and self.options[opt_name].type is bool:
                        raise GetoptError(('Option %s is boolean, must not '
                                           'have arguments') % opt_name)

                    if not opt_val:
                        opt_val = True

                    opts.append((opt_name, opt_val))
                    opt_name = ''
                    opt_val = ''

                # Save new name
                opt_name = arg_str

            else:
                if opt_val:
                    raise GetoptError(('Option must not have more than 1 '
                                       'argument: %s') % opt_name)

                opt_val = arg_str

        return opts

    def check_opts_name(self, opts):
        # Check for right opt names
        for opt_name, opt_val in opts:
            if opt_name not in self.options:
                raise GetoptError('No such option: %s' % opt_name)

    def check_all_mandatory_used(self, opts):
        # Dict mandatory_opt_name : usage
        used_mandatory = {}

        for opt_name, opt_opt in self.options.iteritems():
            if opt_opt.mandatory:
                used_mandatory[opt_name] = False

        # Check in opts
        for opt_name, opt_val in opts:
            # Mark if mandatory used
            if opt_name in used_mandatory:
                used_mandatory[opt_name] = True

        # Chack if all mandatory used
        if not all([used for _, used in used_mandatory.iteritems()]):
            raise GetoptError('Not all mandatory options were used')

    def convert_opt_values2opt_type(self, opts):
        opts_converted = []

        for i, (opt_name, opt_val) in enumerate(opts):

            try:
                # Convert str value to appropriate option value type
                val_converted = self.options[opt_name].type(opt_val)

                opts_converted.append((opt_name, val_converted))

            except ValueError:
                raise GetoptError(('Option %s must have argument of type "%s",'
                                   'got "%s"') %
                                  (opt_name,
                                  self.options[opt_name].type.__name__,
                                  opt_val))

        return opts_converted

    def print_usage(self):
        help_str = 'cmd_args_parsing.py'

        for opt_name in self.options:

            opt_str = opt_name

            if self.options[opt_name].type is not bool:
                opt_str += '=val-of-' + \
                           self.options[opt_name].type.__name__ + \
                           '-type'

            if not self.options[opt_name].mandatory:
                opt_str = '[' + opt_str + ']'

            help_str += ' ' + opt_str

        print(help_str)


def getopt(argv, all_opts):
    try:
        args = list(itertools.chain(*[x.split('=') for x in argv]))

        if '--help' in args:
            all_opts.print_usage()
            return

        # Parse arguments, check for number of arguments for options
        opts = all_opts.parse_argv(args)

        # Check for right option names
        all_opts.check_opts_name(opts)

        # Check for right mandatory options usage
        all_opts.check_all_mandatory_used(opts)

        # Check for right value types and convert str to theese types
        opts_converted = all_opts.convert_opt_values2opt_type(opts)

    except GetoptError as ge:
        print(ge.message)

    else:
        return opts_converted


def create_available_options_lst():
    all_opts = AvailableOptions()
    all_opts.options['--help'] = OptionTypeMandatory(bool,  False)
    all_opts.options['--opt-name-1'] = OptionTypeMandatory(int,   True)
    all_opts.options['--opt-name-2'] = OptionTypeMandatory(float, True)
    all_opts.options['--opt-name-3'] = OptionTypeMandatory(str,   False)
    all_opts.options['--opt-name-4'] = OptionTypeMandatory(bool,  False)

    return all_opts


def main(argv):
    all_opts = create_available_options_lst()

    opts = getopt(argv, all_opts)

    if opts:
        print('Options: ')
        print(opts)

if __name__ == '__main__':
    main(sys.argv[1:])


def test():
    print('run cmd_args_parsing.py')
    main(''.split())
    print('')

    print('run cmd_args_parsing.py --opt-wrong-name')
    main('--opt-wrong-name'.split())
    print('')

    print('run cmd_args_parsing.py --opt-name-1=1')
    main('--opt-name-1=1'.split())
    print('')

    print('run cmd_args_parsing.py --opt-name-2 arg1 arg2')
    main('--opt-name-2 arg1 arg2'.split())
    print('')

    print('run cmd_args_parsing.py --opt-name-4 useless_arg')
    main('--opt-name-4 useless_arg'.split())
    print('')

    print('run cmd_args_parsing.py --opt-name-1 '
          'opt-val-wrong-type --opt-name-2 2.4')
    main('--opt-name-1 opt-val-wrong-type --opt-name-2 2.4'.split())
    print('')

    print('run cmd_args_parsing.py --opt-name-1=1 '
          '--opt-name-2 2.4 --opt-name-3 val --opt-name-4')
    main(('--opt-name-1=1 --opt-name-2 2.4'
          '--opt-name-3 val --opt-name-4').split())
    print('')

    print('run cmd_args_parsing.py --opt-name-1 -1 '
          '--opt-name-2=-2.4 --opt-name-4')
    main('--opt-name-1 -1 --opt-name-2=-2.4 --opt-name-4'.split())
    print('')

    print('run cmd_args_parsing.py --help')
    main('--help'.split())
    print('')

    print('run cmd_args_parsing.py something --help')
    main('something --help'.split())
    print('')
