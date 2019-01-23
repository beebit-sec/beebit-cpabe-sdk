import pycpabe
pycpabe.cpabe_setup('pk','mk')
pycpabe.cpabe_vkeygen('sk1', 'pk', 'mk', 2, ['bob','age = 20'])
pycpabe.cpabe_vkeygen('sk2','pk','mk',2,['alice','age = 10'])
#pycpabe.cpabe_fenc('pk','data','age > 15', 'data.enc')
pycpabe.cpabe_fdec('pk','sk1','data.enc', 'data')


