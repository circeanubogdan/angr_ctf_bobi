#!/usr/bin/env python

import sys, random, os, tempfile
sys.path.append('/home/jake/templite')
from templite import Templite

userdef_charset = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'
userdef = ''.join(random.choice(userdef_charset) for _ in range(8))
template = open('12_angr_locate_vulnerable.c.templite', 'r').read()
c_code = Templite(template).render(userdef=userdef)
print userdef
print c_code
with tempfile.NamedTemporaryFile(delete=False, suffix='.c') as temp:
  temp.write(c_code)
  temp.seek(0)
  os.system('gcc -m32 -o 12_angr_locate_vulnerable ' + temp.name)