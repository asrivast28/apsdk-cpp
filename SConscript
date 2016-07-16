import platform

Import('env')

libName = 'apsdk'

cppLibs = [
           'apexec',
           'apcompile',
           ]

srcFiles = [
            'AnmlMacro.cpp',
            'AnmlNetwork.cpp',
            'Automaton.cpp',
            'Anml.cpp',
            ]

#apsdk = env.StaticLibrary(target = libName, source = srcFiles, LIBS = cppLibs)
apsdk = env.SharedLibrary(target = libName, source = srcFiles, LIBS = cppLibs)
Return("apsdk")
