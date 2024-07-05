from distutils.core import setup, Extension

def main():
    setup(name="syscalls",
          version="1.0.0",
          description="Python wrapper for FreeBSD14.0 L4S system calls.",
          author="Deol Satish",
          author_email="deol.satish@deakin.edu.au",
          ext_modules=[Extension("syscalls", ["py_l4s_syscall.c"])])

if __name__ == "__main__":
    main()