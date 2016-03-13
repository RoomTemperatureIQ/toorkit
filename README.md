# toorkit

A simple useless rootkit for the linux kernel. It basically a kernel module which hooks up the open() syscall (or potentially any syscall) to replace it with a custom function.
