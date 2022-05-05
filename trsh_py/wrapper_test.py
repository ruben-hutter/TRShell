# test code for the wrapper demo
import wrapper as wrp

if __name__ == "__main__":
    # create wrapper
    wrap = wrp.Wrapper(None)
    # spam stdin
    wrap.push_to_shell("Test string")