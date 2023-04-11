# qemu-set-display

A dummy VNC client used to connect and set up a multi-head qemu display.

When using the "max_outputs" setting on a virtio-vga/virtio-gpu qemu display,
only the first display will register in the guest as being connected. 

Additional connectors must be enabled by connecting a UI frontend before
they are usable by the guest.

This tool can be used to make that connection and initialize the
additional displays in the guest VM.

## Requirements

libvncclient (>=0.9.14 or patched to support SetDesktopSize )

## build

```
  $ meson build
  $ ninja -C build install
```

## Usage

### qemu

Each output needs to be set up on its own vnc server.
eg. options for 2 servers

```
-device virtio-vga,max_outputs=2,id=mydisp \
  -display vnc=<server1>,display=mydisp,head=0 \
  -display vnc=<server2>,display=mydisp,head=1
```

### qemu-set-display

The `-w` and `-h` options can be used to set the preferred video mode
of the virtual output on each guest connector

```
  qemu-set-display -w 1280 -h 720 <server1>
```
