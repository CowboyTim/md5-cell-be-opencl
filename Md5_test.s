	.file	"Md5_test.s"
.text
	.align	3
	.global	endian_swap
	.type	endian_swap, @function
endian_swap:
	ilhu	$16,255
	lqd	$18,0($3)
	ila	$4,65280
	hbr	.L3,$lr
	cwd	$9,0($3)
	rotqby	$17,$18,$3
	shli	$15,$17,8
	rotmi	$13,$17,-24
	rotmi	$12,$17,-8
	shli	$2,$17,24
	and	$14,$15,$16
	or	$11,$13,$14
	and	$5,$12,$4
	or	$6,$11,$2
	or	$7,$5,$6
	shufb	$8,$7,$18,$9
	stqd	$8,0($3)
.L3:
	bi	$lr
	.size	endian_swap, .-endian_swap
	.section	.rodata.str1.16,"aMS",@progbits,1
	.align	4
.LC0:
	.string	"v:%d, %08x%08x%08x%08x"
	.align	4
.LC1:
	.string	" \"%s\"\n"
.text
	.align	3
	.global	MD5Print
	.type	MD5Print, @function
MD5Print:
	hbrr	.L11,printf
	stqd	$80,-16($sp)
	il	$80,0
	hbrp	# 1
	nop	127
	stqd	$81,-32($sp)
	ilhu	$81,255
	stqd	$82,-48($sp)
	ila	$82,65280
	stqd	$83,-64($sp)
	il	$83,0
	stqd	$84,-80($sp)
	ori	$84,$3,0
	stqd	$lr,16($sp)
	stqd	$sp,-112($sp)
	ai	$sp,$sp,-112
.L5:
	ori	$4,$83,0
	hbrp	# 2
	nop	127
	lqr	$44,aa
	ai	$83,$83,1
	lqr	$43,bb
	ila	$3,.LC0
	lqr	$42,cc
	lqr	$41,dd
	rotqby	$39,$44,$80
	rotqby	$37,$43,$80
	rotqby	$35,$42,$80
	rotqby	$33,$41,$80
	shli	$40,$39,8
	shli	$38,$37,8
	shli	$36,$35,8
	shli	$34,$33,8
	rotmi	$31,$39,-24
	rotmi	$29,$37,-24
	rotmi	$27,$35,-24
	rotmi	$26,$33,-24
	rotmi	$23,$39,-8
	rotmi	$22,$37,-8
	rotmi	$21,$35,-8
	rotmi	$20,$33,-8
	and	$32,$40,$81
	shli	$11,$39,24
	and	$30,$38,$81
	shli	$10,$37,24
	and	$28,$36,$81
	shli	$9,$35,24
	and	$12,$34,$81
	shli	$24,$33,24
	or	$25,$31,$32
	or	$19,$29,$30
	or	$18,$27,$28
	or	$13,$26,$12
	or	$5,$25,$11
	or	$6,$19,$10
	or	$7,$18,$9
	or	$8,$13,$24
	and	$14,$23,$82
	and	$15,$22,$82
	and	$16,$21,$82
	and	$17,$20,$82
	or	$5,$14,$5
	or	$6,$15,$6
	or	$7,$16,$7
	or	$8,$17,$8
.L11:
	brsl	$lr,printf
	ila	$3,.LC1
	shlqbyi	$4,$84,0
	ai	$80,$80,4
	brsl	$lr,printf
	ceqi	$2,$83,4
	brz	$2,.L5
	ai	$sp,$sp,112
	lqd	$lr,16($sp)
	lqd	$80,-16($sp)
	lqd	$81,-32($sp)
	lqd	$82,-48($sp)
	lqd	$83,-64($sp)
	lqd	$84,-80($sp)
	bi	$lr
	.size	MD5Print, .-MD5Print
	.align	3
	.global	new_MD5Calc
	.type	new_MD5Calc, @function
        .equ S11,7
        .equ S12,12
        .equ S13,17
        .equ S14,22
        .equ S21,5
        .equ S22,9
        .equ S23,14
        .equ S24,20
        .equ S31,4
        .equ S32,11
        .equ S33,16
        .equ S34,23
        .equ S41,6
        .equ S42,10
        .equ S43,15
        .equ S44,21
    .equ k0 ,127
    .equ k1 ,126
    .equ k2 ,125
    .equ k3 ,124
    .equ k4 ,123
    .equ k5 ,122
    .equ k6 ,121
    .equ k7 ,120
    .equ k8 ,119
    .equ k9 ,118
    .equ k10,117
    .equ k11,116
    .equ k12,115
    .equ k13,114
    .equ k14,113
    .equ k15,112
    .equ k16,111
    .equ k17,110
    .equ k18,109
    .equ k19,108
    .equ k20,107
    .equ k21,106
    .equ k22,105
    .equ k23,104
    .equ k24,103
    .equ k25,102
    .equ k26,101
    .equ k27,100
    .equ k28, 99
    .equ k29, 98
    .equ k30, 97
    .equ k31, 96
    .equ k32, 95
    .equ k33, 94
    .equ k34, 93
    .equ k35, 92
    .equ k36, 91
    .equ k37, 90
    .equ k38, 89
    .equ k39, 88
    .equ k40, 87
    .equ k41, 86
    .equ k42, 85
    .equ k43, 84
    .equ k44, 83
    .equ k45, 82
    .equ k46, 81
    .equ k47, 80
    .equ k48, 79
    .equ k49, 78
    .equ k50, 77
    .equ k51, 76
    .equ k52, 75
    .equ k53, 74
    .equ k54, 73
    .equ k55, 72
    .equ k56, 71
    .equ k57, 70
    .equ k58, 69
    .equ k59, 68
    .equ k60, 67
    .equ k61, 66
    .equ k62, 65
    .equ k63, 64
        .equ DIGEST_W_H0, 63
        .equ DIGEST_W_H1, 62
        .equ DIGEST_W_H2, 61
        .equ DIGEST_W_H3, 60
        .equ Ac, 59
        .equ Bc, 58
        .equ Cc, 57
        .equ Dc, 56
        .equ in0, 55
        .equ in1, 54
        .equ in2, 53
        .equ in3, 52
        .equ in4, 51
        .equ a, 50
        .equ b, 49
        .equ c, 48
        .equ d, 47
        .equ s0, 46
        .equ s1, 45
        .equ s2, 44
        .equ bit, 43
        .equ original_string, 42
        .equ counter, 41

.macro FF a,b,c,d,x,s,ac
    and  $s0, \a,   \b
    andc $s1, \c,   \a
    or   $s2, $s0,  $s1

    a    $s0, \x,   \ac
    a    $s1, $s0,  $s2
    a    $s0, $s1,  \a
    roti $s1, $s0,  \s
    a    \a,  \b,   $s1
.endm

.macro FF_NOX a,b,c,d,s,ac
    and  $s0, \a,   \b
    andc $s1, \c,   \a
    or   $s2, $s0,  $s1

    a    $s1, \ac,  $s2
    a    $s0, $s1,  \a
    roti $s1, $s0,  \s
    a    \a,  \b,   $s1
.endm

.macro GG a,b,c,d,x,s,ac
    and  $s0, \b,   \d
    andc $s1, \c,   \d
    or   $s2, $s0,  $s1

    a    $s0, \x,   \ac
    a    $s1, $s0,  $s2
    a    $s0, $s1,  \a
    roti $s1, $s0,  \s
    a    \a,  \b,   $s1
.endm

.macro GG_NOX a,b,c,d,s,ac
    and  $s0, \b,   \d
    andc $s1, \c,   \d
    or   $s2, $s0,  $s1

    a    $s1, \ac,  $s2
    a    $s0, $s1,  \a
    roti $s1, $s0,  \s
    a    \a,  \b,   $s1
.endm

.macro HH a,b,c,d,x,s,ac
    xor  $s0, \b,   \c
    xor  $s2, $s0,  \d

    a    $s0, \x,   \ac
    a    $s1, $s0,  $s2
    a    $s0, $s1,  \a
    roti $s1, $s0,  \s
    a    \a,  \b,   $s1
.endm

.macro HH_NOX a,b,c,d,s,ac
    xor  $s0, \b,   \c
    xor  $s2, $s0,  \d

    a    $s1, \ac,  $s2
    a    $s0, $s1,  \a
    roti $s1, $s0,  \s
    a    \a,  \b,   $s1
.endm

.macro II a,b,c,d,x,s,ac
    orc  $s0, \b,   \d
    xor  $s2, $s0,  \c

    a    $s0, \x,   \ac
    a    $s1, $s0,  $s2
    a    $s0, $s1,  \a
    roti $s1, $s0,  \s
    a    \a,  \b,   $s1
.endm

.macro II_NOX a,b,c,d,s,ac
    orc  $s0, \b,   \d
    xor  $s2, $s0,  \c

    a    $s1, \ac,  $s2
    a    $s0, $s1,  \a
    roti $s1, $s0,  \s
    a    \a,  \b,   $s1
.endm

new_MD5Calc:
    /* Keep all the constants k in the registers */
    lqr $k0 , k+(16* 0)
    lqr $k1 , k+(16* 1)
    lqr $k2 , k+(16* 2)
    lqr $k3 , k+(16* 3)
    lqr $k4 , k+(16* 4)
    lqr $k5 , k+(16* 5)
    lqr $k6 , k+(16* 6)
    lqr $k7 , k+(16* 7)
    lqr $k8 , k+(16* 8)
    lqr $k9 , k+(16* 9)
    lqr $k10, k+(16*10)
    lqr $k11, k+(16*11)
    lqr $k12, k+(16*12)
    lqr $k13, k+(16*13)
    lqr $k14, k+(16*14)
    lqr $k15, k+(16*15)
    lqr $k16, k+(16*16)
    lqr $k17, k+(16*17)
    lqr $k18, k+(16*18)
    lqr $k19, k+(16*19)
    lqr $k20, k+(16*20)
    lqr $k21, k+(16*21)
    lqr $k22, k+(16*22)
    lqr $k23, k+(16*23)
    lqr $k24, k+(16*24)
    lqr $k25, k+(16*25)
    lqr $k26, k+(16*26)
    lqr $k27, k+(16*27)
    lqr $k28, k+(16*28)
    lqr $k29, k+(16*29)
    lqr $k30, k+(16*30)
    lqr $k31, k+(16*31)
    lqr $k32, k+(16*32)
    lqr $k33, k+(16*33)
    lqr $k34, k+(16*34)
    lqr $k35, k+(16*35)
    lqr $k36, k+(16*36)
    lqr $k37, k+(16*37)
    lqr $k38, k+(16*38)
    lqr $k39, k+(16*39)
    lqr $k40, k+(16*40)
    lqr $k41, k+(16*41)
    lqr $k42, k+(16*42)
    lqr $k43, k+(16*43)
    lqr $k44, k+(16*44)
    lqr $k45, k+(16*45)
    lqr $k46, k+(16*46)
    lqr $k47, k+(16*47)
    lqr $k48, k+(16*48)
    lqr $k49, k+(16*49)
    lqr $k50, k+(16*50)
    lqr $k51, k+(16*51)
    lqr $k52, k+(16*52)
    lqr $k53, k+(16*53)
    lqr $k54, k+(16*54)
    lqr $k55, k+(16*55)
    lqr $k56, k+(16*56)
    lqr $k57, k+(16*57)
    lqr $k58, k+(16*58)
    lqr $k59, k+(16*59)
    lqr $k60, k+(16*60)
    lqr $k61, k+(16*61)
    lqr $k62, k+(16*62)
    lqr $k63, k+(16*63)

    /* Our digest to check against is constant
       Also our a,b,c,d initializes, keep them in
       the registers...
     */
    lqr  $DIGEST_W_H0, digest_w_h0
    lqr  $DIGEST_W_H1, digest_w_h1
    lqr  $DIGEST_W_H2, digest_w_h2
    lqr  $DIGEST_W_H3, digest_w_h3
    lqr  $Ac, aC
    lqr  $Bc, bC
    lqr  $Cc, cC
    lqr  $Dc, dC

    /* Initialize the inString in0,..,in4 */
    lqr $bit,             bitLen
	lqr	$original_string, inString

	rotqbyi	$s1, $original_string,3
	andi	$s0, $s1,0x00ff
	shli	$in0,$s0,16
	rotqbyi	$s2, $original_string,4
	shli	$s1, $s2,24
	or      $s0, $s1,$in0
	rotqbyi	$in0,$original_string,1
	andi	$s2, $in0,0x00ff
	or	    $s1, $s0,$s2
	rotqbyi	$s0, $original_string,2
	andi	$s2, $s0,0x00ff
	shli	$s0, $s2,8
	or	    $in0,$s0,$s1

	rotqbyi	$s1, $original_string,7
	andi	$s0, $s1,0x00ff
	shli	$in1,$s0,16
	rotqbyi	$s2, $original_string,8
	shli	$s1, $s2,24
	or      $s0, $s1,$in1
	rotqbyi	$in1,$original_string,5
	andi	$s2, $in1,0x00ff
	or	    $s1, $s0,$s2
	rotqbyi	$s0, $original_string,6
	andi	$s2, $s0,0x00ff
	shli	$s0, $s2,8
	or	    $in1,$s0,$s1

	rotqbyi	$s1, $original_string,11
	andi	$s0, $s1,0x00ff
	shli	$in2,$s0,16
	rotqbyi	$s2, $original_string,12
	shli	$s1, $s2,24
	or      $s0, $s1,$in2
	rotqbyi	$in2,$original_string,9
	andi	$s2, $in2,0x00ff
	or	    $s1, $s0,$s2
	rotqbyi	$s0, $original_string,10
	andi	$s2, $s0,0x00ff
	shli	$s0, $s2,8
	or	    $in2,$s0,$s1

	rotqbyi	$s1, $original_string,15
	andi	$s0, $s1,0x00ff
	shli	$in3,$s0,16
	rotqbyi	$s2, $original_string,16
	shli	$s1, $s2,24
	or      $s0, $s1,$in3
	rotqbyi	$in3,$original_string,13
	andi	$s2, $in3,0x00ff
	or	    $s1, $s0,$s2
	rotqbyi	$s0, $original_string,14
	andi	$s2, $s0,0x00ff
	shli	$s0, $s2,8
	or	    $in3,$s0,$s1

    lqr $counter,Counter





    

#.L28:
#	br	.L13
#.L26:
#	#hbrr	.L27,.L26
#	brz	$counter,.L22
.L13:



    /* Initialize our a,b,c,d with the constants */
    ai  $a, $Ac, 0
    ai  $b, $Bc, 0
    ai  $c, $Cc, 0
    ai  $d, $Dc, 0

    /* First FF is a special one */
    a      $s0, $in0,           $k0
    roti   $s1, $s0,        S11
    a      $a,  $b,   $a
    a      $a,  $s1,  $a

    FF     $d,$a,$b,$c,$in1,S12,$k1
    FF     $c,$d,$a,$b,$in2,S13,$k2
    FF     $b,$c,$d,$a,$in3,S14,$k3
    FF     $a,$b,$c,$d,$in4,S11,$k4
    FF_NOX $d,$a,$b,$c,     S12,$k5
    FF_NOX $c,$d,$a,$b,     S13,$k6
    FF_NOX $b,$c,$d,$a,     S14,$k7
    FF_NOX $a,$b,$c,$d,     S11,$k8
    FF_NOX $d,$a,$b,$c,     S12,$k9
    FF_NOX $c,$d,$a,$b,     S13,$k10
    FF_NOX $b,$c,$d,$a,     S14,$k11
    FF_NOX $a,$b,$c,$d,     S11,$k12
    FF_NOX $d,$a,$b,$c,     S12,$k13
    FF     $c,$d,$a,$b,$bit,S13,$k14
    FF_NOX $b,$c,$d,$a,     S14,$k15

    GG     $a,$b,$c,$d,$in1,S21,$k16
    GG_NOX $d,$a,$b,$c,     S22,$k17
    GG_NOX $c,$d,$a,$b,     S23,$k18
    GG     $b,$c,$d,$a,$in0,S24,$k19
    GG_NOX $a,$b,$c,$d,     S21,$k20
    GG_NOX $d,$a,$b,$c,     S22,$k21
    GG_NOX $c,$d,$a,$b,     S23,$k22
    GG     $b,$c,$d,$a,$in4,S24,$k23
    GG_NOX $a,$b,$c,$d,     S21,$k24
    GG     $d,$a,$b,$c,$bit,S22,$k25
    GG     $c,$d,$a,$b,$in3,S23,$k26
    GG_NOX $b,$c,$d,$a,     S24,$k27
    GG_NOX $a,$b,$c,$d,     S21,$k28
    GG     $d,$a,$b,$c,$in2,S22,$k29
    GG_NOX $c,$d,$a,$b,     S23,$k30
    GG_NOX $b,$c,$d,$a,     S24,$k31

    HH_NOX $a,$b,$c,$d,     S31,$k32
    HH_NOX $d,$a,$b,$c,     S32,$k33
    HH_NOX $c,$d,$a,$b,     S33,$k34
    HH     $b,$c,$d,$a,$bit,S34,$k35
    HH     $a,$b,$c,$d,$in1,S31,$k36
    HH     $d,$a,$b,$c,$in4,S32,$k37
    HH_NOX $c,$d,$a,$b,     S33,$k38
    HH_NOX $b,$c,$d,$a,     S34,$k39
    HH_NOX $a,$b,$c,$d,     S31,$k40
    HH     $d,$a,$b,$c,$in0,S32,$k41
    HH     $c,$d,$a,$b,$in3,S33,$k42
    HH_NOX $b,$c,$d,$a,     S34,$k43
    HH_NOX $a,$b,$c,$d,     S31,$k44
    HH_NOX $d,$a,$b,$c,     S32,$k45
    HH_NOX $c,$d,$a,$b,     S33,$k46
    HH     $b,$c,$d,$a,$in2,S34,$k47

    II     $a,$b,$c,$d,$in0,S41,$k48
    II_NOX $d,$a,$b,$c,     S42,$k49
    II     $c,$d,$a,$b,$bit,S43,$k50
    II_NOX $b,$c,$d,$a,     S44,$k51
    II_NOX $a,$b,$c,$d,     S41,$k52
    II     $d,$a,$b,$c,$in3,S42,$k53
    II_NOX $c,$d,$a,$b,     S43,$k54
    II     $b,$c,$d,$a,$in1,S44,$k55
    II_NOX $a,$b,$c,$d,     S41,$k56
    II_NOX $d,$a,$b,$c,     S42,$k57
    II_NOX $c,$d,$a,$b,     S43,$k58
    II_NOX $b,$c,$d,$a,     S44,$k59
    II     $a,$b,$c,$d,$in4,S41,$k60
    II_NOX $d,$a,$b,$c,     S42,$k61
    II     $c,$d,$a,$b,$in2,S43,$k62
    II_NOX $b,$c,$d,$a,     S44,$k63





    ai $counter,$counter, -1
.L27:
	brnz	$counter,.L13
.L22:


	bi	$lr
	.size	new_MD5Calc, .-new_MD5Calc
	.section	.rodata.str1.16
	.align	4
.LC3:
	.string	"%08x%08x%08x%08x"
	.global	__float_unssidf
	.global	__divdf3
	.align	4
.LC4:
	.string	"nrcalcs: %d, ok:%d, calcs per second: %f\n"
	.align	4
.LC2:
	.string	"45ed9cc2f92b77cd8b2f5bd59ff635f8"
	.section	.rodata.cst16,"aM",@progbits,16
	.align	4
.LC5:
	.long	1105199104
	.long	0
	.align	4
	.align	4
.LC6:
	.long	1093567616
	.long	0
	.align	4
	.align	4
.LC7:
	.long	1095963344
	.long	0
	.align	4
.text
	.align	3
	.global	main
	.type	main, @function
main:
	ila	$4,.LC3
	hbrr	.L41,sscanf
	lqr	$79,.LC2+32
	hbrp	# 1
	stqd	$lr,16($sp)
	stqd	$80,-16($sp)
	stqd	$81,-32($sp)
	stqd	$82,-48($sp)
	ilhu	$82,-32768
	stqd	$83,-64($sp)
	nop	127
	stqd	$84,-80($sp)
	ilhu	$84,4146
	stqd	$85,-96($sp)
	ilhu	$85,-26438
	stqd	$86,-112($sp)
	ilhu	$86,26437
	hbrp	# 2
	nop	127
	stqd	$87,-128($sp)
	ilhu	$87,-4147
	hbrp	# 3
	iohl	$86,8961
	stqd	$88,-144($sp)
	iohl	$87,43913
	stqd	$89,-160($sp)
	ila	$89,66051
	stqd	$sp,-352($sp)
	ai	$sp,$sp,-352
	rotqbyi	$75,$79,13
	iohl	$85,56574
	lqr	$78,.LC2
	ai	$5,$sp,32
	lqd	$74,176($sp)
	ai	$6,$sp,48
	cbd	$76,0($sp)
	ai	$7,$sp,64
	lqr	$77,.LC2+16
	ai	$8,$sp,80
	ai	$3,$sp,144
	iohl	$84,21622
	stqd	$78,144($sp)
	ai	$80,$sp,128
	shufb	$73,$75,$74,$76
	stqd	$77,160($sp)
	stqd	$73,176($sp)
	nop	127
.L41:
	brsl	$lr,sscanf
	ilhu	$67,255
	lqd	$32,32($sp)
	ila	$44,65280
	hbrp	# 1
	nop	127
	lqd	$22,48($sp)
	ila	$3,inString
	lqd	$23,64($sp)
	lqd	$34,80($sp)
	hbrr	.L40,strlen
	cwd	$29,0($sp)
	shli	$71,$32,8
	shli	$69,$22,8
	shli	$66,$23,8
	shli	$72,$34,8
	rotmi	$62,$32,-24
	rotmi	$60,$22,-24
	hbrp	# 2
	rotmi	$58,$23,-24
	rotmi	$56,$34,-24
	rotmi	$46,$32,-8
	rotmi	$45,$22,-8
	rotmi	$43,$23,-8
	rotmi	$49,$34,-8
	and	$57,$72,$67
	and	$63,$71,$67
	shli	$55,$32,24
	and	$61,$69,$67
	shli	$53,$22,24
	and	$59,$66,$67
	shli	$51,$23,24
	shli	$48,$34,24
	or	$54,$62,$63
	or	$52,$60,$61
	or	$50,$58,$59
	or	$47,$56,$57
	or	$42,$54,$55
	or	$40,$52,$53
	or	$38,$50,$51
	and	$35,$49,$44
	or	$36,$47,$48
	and	$41,$46,$44
	and	$39,$45,$44
	and	$37,$43,$44
	or	$31,$41,$42
	or	$30,$39,$40
	or	$28,$37,$38
	shufb	$25,$31,$31,$89
	or	$33,$35,$36
	shufb	$24,$30,$30,$89
	shufb	$17,$28,$28,$89
	shufb	$16,$33,$33,$89
	sf	$19,$86,$25
	shufb	$27,$33,$34,$29
	sf	$18,$87,$24
	shufb	$26,$31,$32,$29
	sf	$15,$85,$17
	shufb	$21,$30,$22,$29
	sf	$14,$84,$16
	shufb	$20,$28,$23,$29
	stqd	$27,80($sp)
	stqd	$26,32($sp)
	stqd	$21,48($sp)
	stqd	$20,64($sp)
	stqr	$19,digest_w_h0
	stqr	$18,digest_w_h1
	stqr	$15,digest_w_h2
	stqr	$14,digest_w_h3
.L40:
	brsl	$lr,strlen
	hbrr	.L39,gettimeofday
	shli	$13,$3,3
	lqr	$83,.LC5
	nop	$127
	shlqbyi	$4,$80,0
	ai	$3,$sp,96
	shufb	$12,$13,$13,$89
	il	$89,0
	stqr	$12,bitLen
.L39:
	brsl	$lr,gettimeofday
	ilhu	$3,76
	iohl	$3,19264
    ai   $20, $80, 0
    ai   $22, $81, 0
    ai   $21, $88, 0
	brsl	$lr,new_MD5Calc
	ai	$sp,$sp,352
	lqd	$lr,16($sp)
	lqd	$80,-16($sp)
	lqd	$81,-32($sp)
	lqd	$82,-48($sp)
	lqd	$83,-64($sp)
	lqd	$84,-80($sp)
	hbr	.L36,$lr
	lqd	$85,-96($sp)
	lqd	$86,-112($sp)
	lqd	$87,-128($sp)
	lqd	$88,-144($sp)
	lqd	$89,-160($sp)
.L36:
	bi	$lr
	.size	main, .-main

	.global	inString
.data
	.align	16
	.type	inString, @object
	.size	inString, 16
inString:
	.string	"xxxxxxxxxxxxxxxo"

	.global	Counter
	.align	4
	.type	Counter, @object
	.size	Counter, 16
Counter:
	.long	10000000
	.long	10000000
	.long	10000000
	.long	10000000

	.global	bC
	.align	4
	.type	bC, @object
	.size	bC, 16
aC:
	.long	1732584193
	.long	1732584193
	.long	1732584193
	.long	1732584193
	.global	bC
	.align	4
	.type	bC, @object
	.size	bC, 16
bC:
	.long	-271733879
	.long	-271733879
	.long	-271733879
	.long	-271733879
	.global	cC
	.align	4
	.type	cC, @object
	.size	cC, 16
cC:
	.long	-1732584194
	.long	-1732584194
	.long	-1732584194
	.long	-1732584194
	.global	dC
	.align	4
	.type	dC, @object
	.size	dC, 16
dC:
	.long	271733878
	.long	271733878
	.long	271733878
	.long	271733878
	.global	in0
	.section .bss
	.align	4
	.type	in0, @object
	.size	in0, 16
in0:
	.space	16
	.global	in1
	.align	4
	.type	in1, @object
	.size	in1, 16
in1:
	.space	16
	.global	in2
	.align	4
	.type	in2, @object
	.size	in2, 16
in2:
	.space	16
	.global	in3
	.align	4
	.type	in3, @object
	.size	in3, 16
in3:
	.space	16
	.global	in4
.data
	.align	4
	.type	in4, @object
	.size	in4, 16
in4:
	.long	128
	.long	128
	.long	128
	.long	128
	.global	k
	.align	4
	.type	k, @object
	.size	k, 1024
k:
	.long	-680876936
	.long	-680876936
	.long	-680876936
	.long	-680876936
	.long	-389564586
	.long	-389564586
	.long	-389564586
	.long	-389564586
	.long	606105819
	.long	606105819
	.long	606105819
	.long	606105819
	.long	-1044525330
	.long	-1044525330
	.long	-1044525330
	.long	-1044525330
	.long	-176418897
	.long	-176418897
	.long	-176418897
	.long	-176418897
	.long	1200080426
	.long	1200080426
	.long	1200080426
	.long	1200080426
	.long	-1473231341
	.long	-1473231341
	.long	-1473231341
	.long	-1473231341
	.long	-45705983
	.long	-45705983
	.long	-45705983
	.long	-45705983
	.long	1770035416
	.long	1770035416
	.long	1770035416
	.long	1770035416
	.long	-1958414417
	.long	-1958414417
	.long	-1958414417
	.long	-1958414417
	.long	-42063
	.long	-42063
	.long	-42063
	.long	-42063
	.long	-1990404162
	.long	-1990404162
	.long	-1990404162
	.long	-1990404162
	.long	1804603682
	.long	1804603682
	.long	1804603682
	.long	1804603682
	.long	-40341101
	.long	-40341101
	.long	-40341101
	.long	-40341101
	.long	-1502002290
	.long	-1502002290
	.long	-1502002290
	.long	-1502002290
	.long	1236535329
	.long	1236535329
	.long	1236535329
	.long	1236535329
	.long	-165796510
	.long	-165796510
	.long	-165796510
	.long	-165796510
	.long	-1069501632
	.long	-1069501632
	.long	-1069501632
	.long	-1069501632
	.long	643717713
	.long	643717713
	.long	643717713
	.long	643717713
	.long	-373897302
	.long	-373897302
	.long	-373897302
	.long	-373897302
	.long	-701558691
	.long	-701558691
	.long	-701558691
	.long	-701558691
	.long	38016083
	.long	38016083
	.long	38016083
	.long	38016083
	.long	-660478335
	.long	-660478335
	.long	-660478335
	.long	-660478335
	.long	-405537848
	.long	-405537848
	.long	-405537848
	.long	-405537848
	.long	568446438
	.long	568446438
	.long	568446438
	.long	568446438
	.long	-1019803690
	.long	-1019803690
	.long	-1019803690
	.long	-1019803690
	.long	-187363961
	.long	-187363961
	.long	-187363961
	.long	-187363961
	.long	1163531501
	.long	1163531501
	.long	1163531501
	.long	1163531501
	.long	-1444681467
	.long	-1444681467
	.long	-1444681467
	.long	-1444681467
	.long	-51403784
	.long	-51403784
	.long	-51403784
	.long	-51403784
	.long	1735328473
	.long	1735328473
	.long	1735328473
	.long	1735328473
	.long	-1926607734
	.long	-1926607734
	.long	-1926607734
	.long	-1926607734
	.long	-378558
	.long	-378558
	.long	-378558
	.long	-378558
	.long	-2022574463
	.long	-2022574463
	.long	-2022574463
	.long	-2022574463
	.long	1839030562
	.long	1839030562
	.long	1839030562
	.long	1839030562
	.long	-35309556
	.long	-35309556
	.long	-35309556
	.long	-35309556
	.long	-1530992060
	.long	-1530992060
	.long	-1530992060
	.long	-1530992060
	.long	1272893353
	.long	1272893353
	.long	1272893353
	.long	1272893353
	.long	-155497632
	.long	-155497632
	.long	-155497632
	.long	-155497632
	.long	-1094730640
	.long	-1094730640
	.long	-1094730640
	.long	-1094730640
	.long	681279174
	.long	681279174
	.long	681279174
	.long	681279174
	.long	-358537222
	.long	-358537222
	.long	-358537222
	.long	-358537222
	.long	-722521979
	.long	-722521979
	.long	-722521979
	.long	-722521979
	.long	76029189
	.long	76029189
	.long	76029189
	.long	76029189
	.long	-640364487
	.long	-640364487
	.long	-640364487
	.long	-640364487
	.long	-421815835
	.long	-421815835
	.long	-421815835
	.long	-421815835
	.long	530742520
	.long	530742520
	.long	530742520
	.long	530742520
	.long	-995338651
	.long	-995338651
	.long	-995338651
	.long	-995338651
	.long	-198630844
	.long	-198630844
	.long	-198630844
	.long	-198630844
	.long	1126891415
	.long	1126891415
	.long	1126891415
	.long	1126891415
	.long	-1416354905
	.long	-1416354905
	.long	-1416354905
	.long	-1416354905
	.long	-57434055
	.long	-57434055
	.long	-57434055
	.long	-57434055
	.long	1700485571
	.long	1700485571
	.long	1700485571
	.long	1700485571
	.long	-1894986606
	.long	-1894986606
	.long	-1894986606
	.long	-1894986606
	.long	-1051523
	.long	-1051523
	.long	-1051523
	.long	-1051523
	.long	-2054922799
	.long	-2054922799
	.long	-2054922799
	.long	-2054922799
	.long	1873313359
	.long	1873313359
	.long	1873313359
	.long	1873313359
	.long	-30611744
	.long	-30611744
	.long	-30611744
	.long	-30611744
	.long	-1560198380
	.long	-1560198380
	.long	-1560198380
	.long	-1560198380
	.long	1309151649
	.long	1309151649
	.long	1309151649
	.long	1309151649
	.long	-145523070
	.long	-145523070
	.long	-145523070
	.long	-145523070
	.long	-1120210379
	.long	-1120210379
	.long	-1120210379
	.long	-1120210379
	.long	718787259
	.long	718787259
	.long	718787259
	.long	718787259
	.long	-343485551
	.long	-343485551
	.long	-343485551
	.long	-343485551
	.comm	aa,16,16
	.comm	bb,16,16
	.comm	cc,16,16
	.comm	dd,16,16
	.comm	bitLen,16,16
	.comm	digest_w_h0,16,16
	.comm	digest_w_h1,16,16
	.comm	digest_w_h2,16,16
	.comm	digest_w_h3,16,16
	.ident	"GCC: (GNU) 4.1.1"
