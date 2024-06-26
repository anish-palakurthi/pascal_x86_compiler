        .file   "foo"
        .text
        .globl graph1
        .type   graph1, @function
graph1:
.LFB0:
	.cfi_startproc
	pushq	%rbp              # save base pointer on stack
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp        # move stack pointer to base pointer
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
        subq	$32, %rsp 	  # make space for this stack frame
	movq	%rbx, %r9        # save %rbx (callee-saved) in %r9
# ------------------------- begin Your code -----------------------------
	movsd	-32(%rbp),%xmm0     	#  x -> %xmm0
	call	exp@PLT          	#  exp()
	movsd	%xmm1,-8(%rbp)     	#  %xmm1 -> temp
	movsd	-32(%rbp),%xmm0     	#  x -> %xmm0
	call	sin@PLT          	#  sin()
	movsd	-8(%rbp),%xmm1     	#  temp -> %xmm1
	mulsd	%xmm1,%xmm0         	#  %xmm0 * %xmm1 -> %xmm0
	movsd	%xmm0,-24(%rbp)     	#  %xmm0 -> y
	movsd	-24(%rbp),%xmm0     	#  y -> %xmm0
	movsd	%xmm0,%edi         	#  %xmm0 -> %edi
	call	writelnf@PLT          	#  writelnf()
# ----------------------- begin Epilogue code ---------------------------
	movq	%r9, %rbx        # restore %rbx (callee-saved) from %r9
        leave
        ret
        .cfi_endproc
.LFE0:
        .size   graph1, .-graph1
# ----------------- end Epilogue; Literal data follows ------------------
        .section        .rodata

        .ident  "CS 375 Compiler - Spring 2024"
