import platform

Import('env')

libName = 'apsdk'

cppLibs = [
           'apexec',
           'apcompile',
           ]

srcFiles = [
            'SymbolChange.cpp',
            'AnmlMacro.cpp',
            'AnmlNetwork.cpp',
            'Automaton.cpp',
            'ElementMap.cpp',
            'ElementRef.cpp',
            'Anml.cpp',
            ]

#apsdk = env.StaticLibrary(target = libName, source = srcFiles, LIBS = cppLibs)
apsdk = env.SharedLibrary(target = libName, source = srcFiles, LIBS = cppLibs)
Return("apsdk")
