import ctypes
import pathlib

class Grammar:
    
    clib = ctypes.CDLL(pathlib.Path().absolute() / "cbnf.so")

    clib.createGrammar.argtypes = [ ctypes.c_char_p ]
    clib.createGrammar.restype = ctypes.c_void_p

    clib.deleteGrammar.argtypes = [ ctypes.c_void_p ]
    clib.deleteGrammar.restype = None

    clib.getNonTerminal.argtypes = [ ctypes.c_void_p, ctypes.c_char_p ]
    clib.getNonTerminal.restype = ctypes.c_void_p

    clib.getCardinality.argtypes = [ ctypes.c_void_p, ctypes.c_uint ]
    clib.getCardinality.restype = ctypes.c_void_p

    clib.getElement.argtypes = [ ctypes.c_void_p, ctypes.c_uint, ctypes.c_char_p ]
    clib.getElement.restype = ctypes.c_void_p

    clib.getElements.argtypes = [ ctypes.c_void_p, ctypes.c_uint ]
    clib.getElements.restype = ctypes.c_void_p

    clib.freePtr.argtypes = [ ctypes.c_void_p ]
    clib.freePtr.restype = None

    clib.freePtrArray.argtypes = [ ctypes.c_void_p ]
    clib.freePtrArray.restype = None

    clib.getPtrArrayElement.argtypes = [ ctypes.c_void_p, ctypes.c_uint ]
    clib.getPtrArrayElement.restype = ctypes.c_void_p

    def cstr(str):
        return ctypes.c_char_p(bytes(str, encoding="utf-8"))

    def voidptr(ptr):
        return ctypes.c_void_p(ptr)

    def uint(ui):
        return ctypes.c_uint(ui)
    
    def __init__(self, file):
        self.file = file
        self.gptr = Grammar.clib.createGrammar(Grammar.cstr(file))
    
    def __del__(self):
        Grammar.clib.deleteGrammar(Grammar.voidptr(self.gptr))
    
    def __repr__(self):
        return "Grammar('" + self.file + "')"
    
    def getNonTerminal(self, name):
        return Grammar.NonTerminal(Grammar.clib.getNonTerminal(Grammar.voidptr(self.gptr), Grammar.cstr(name)))

    def __getitem__(self, name):
        return self.getNonTerminal(name)

    class NonTerminal:
        
        def __init__(self, ntptr):
            self.ntptr = ntptr
        
        def __repr__(self):
            return "NonTerminal()"
        
        def getCardinality(self, n):
            cstr = Grammar.clib.getCardinality(Grammar.voidptr(self.ntptr), Grammar.uint(n))
            card = int(ctypes.c_char_p(cstr).value)
            Grammar.clib.freePtr(Grammar.voidptr(cstr))
            return card
        
        def getElement(self, n, id):
            cstr = Grammar.clib.getElement(Grammar.voidptr(self.ntptr), Grammar.uint(n), Grammar.cstr(str(id)))
            element = ctypes.c_char_p(cstr).value.decode("utf-8")
            Grammar.clib.freePtr(Grammar.voidptr(cstr))
            return element
        
        def getElements(self, n):
            elements = set()
            cstrArray = Grammar.clib.getElements(Grammar.voidptr(self.ntptr), Grammar.uint(n))
            i = 0
            while True:
                element = Grammar.clib.getPtrArrayElement(Grammar.voidptr(cstrArray), Grammar.uint(i))
                if element is None:
                    break
                elements.add(ctypes.c_char_p(element).value.decode("utf-8"))
                i += 1
            Grammar.clib.freePtrArray(Grammar.voidptr(cstrArray))
            return elements