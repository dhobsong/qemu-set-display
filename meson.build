project('qemu-set-display', 'c')

src = ['qemu-set-display.c']
vnclib = dependency('libvncclient')

executable('qemu-set-display', src,
  dependencies: vnclib,
  install: true)
