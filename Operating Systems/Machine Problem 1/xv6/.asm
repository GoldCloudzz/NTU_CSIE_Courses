
user/_mp1-part2-2:     file format elf64-littleriscv


Disassembly of section .text:

0000000000000000 <s4>:
        thread_yield();
    }
}

void s4(int signo)
{
       0:	1141                	addi	sp,sp,-16
       2:	e406                	sd	ra,8(sp)
       4:	e022                	sd	s0,0(sp)
       6:	0800                	addi	s0,sp,16
       8:	85aa                	mv	a1,a0
    printf("handler 4: %d\n", signo);
       a:	00001517          	auipc	a0,0x1
       e:	ffe50513          	addi	a0,a0,-2 # 1008 <thread_kill+0x16>
      12:	00001097          	auipc	ra,0x1
      16:	9e8080e7          	jalr	-1560(ra) # 9fa <printf>
}
      1a:	60a2                	ld	ra,8(sp)
      1c:	6402                	ld	s0,0(sp)
      1e:	0141                	addi	sp,sp,16
      20:	8082                	ret

0000000000000022 <s3>:


void s3(int signo)
{
      22:	1141                	addi	sp,sp,-16
      24:	e406                	sd	ra,8(sp)
      26:	e022                	sd	s0,0(sp)
      28:	0800                	addi	s0,sp,16
      2a:	85aa                	mv	a1,a0
    printf("handler 3: %d\n", signo);
      2c:	00001517          	auipc	a0,0x1
      30:	fec50513          	addi	a0,a0,-20 # 1018 <thread_kill+0x26>
      34:	00001097          	auipc	ra,0x1
      38:	9c6080e7          	jalr	-1594(ra) # 9fa <printf>
}
      3c:	60a2                	ld	ra,8(sp)
      3e:	6402                	ld	s0,0(sp)
      40:	0141                	addi	sp,sp,16
      42:	8082                	ret

0000000000000044 <s5>:
{
      44:	7139                	addi	sp,sp,-64
      46:	fc06                	sd	ra,56(sp)
      48:	f822                	sd	s0,48(sp)
      4a:	f426                	sd	s1,40(sp)
      4c:	f04a                	sd	s2,32(sp)
      4e:	ec4e                	sd	s3,24(sp)
      50:	e852                	sd	s4,16(sp)
      52:	e456                	sd	s5,8(sp)
      54:	0080                	addi	s0,sp,64
      56:	89aa                	mv	s3,a0
      58:	4965                	li	s2,25
    int i = 5;
      5a:	4495                	li	s1,5
        else printf("handler 5: %d\n", i*5+1);
      5c:	00001a97          	auipc	s5,0x1
      60:	fcca8a93          	addi	s5,s5,-52 # 1028 <thread_kill+0x36>
        if(i == 8) {
      64:	4a21                	li	s4,8
      66:	a01d                	j	8c <s5+0x48>
        if(signo) printf("handler 5: %d\n", i*5);
      68:	85ca                	mv	a1,s2
      6a:	8556                	mv	a0,s5
      6c:	00001097          	auipc	ra,0x1
      70:	98e080e7          	jalr	-1650(ra) # 9fa <printf>
        i++;
      74:	2485                	addiw	s1,s1,1
        if(i == 8) {
      76:	01449663          	bne	s1,s4,82 <s5+0x3e>
            thread_exit();
      7a:	00001097          	auipc	ra,0x1
      7e:	c7e080e7          	jalr	-898(ra) # cf8 <thread_exit>
        thread_yield();
      82:	00001097          	auipc	ra,0x1
      86:	e96080e7          	jalr	-362(ra) # f18 <thread_yield>
    while(1) {
      8a:	2915                	addiw	s2,s2,5
        if(signo) printf("handler 5: %d\n", i*5);
      8c:	fc099ee3          	bnez	s3,68 <s5+0x24>
        else printf("handler 5: %d\n", i*5+1);
      90:	0019059b          	addiw	a1,s2,1
      94:	8556                	mv	a0,s5
      96:	00001097          	auipc	ra,0x1
      9a:	964080e7          	jalr	-1692(ra) # 9fa <printf>
      9e:	bfd9                	j	74 <s5+0x30>

00000000000000a0 <s2>:

void s2(int signo)
{   
      a0:	7179                	addi	sp,sp,-48
      a2:	f406                	sd	ra,40(sp)
      a4:	f022                	sd	s0,32(sp)
      a6:	ec26                	sd	s1,24(sp)
      a8:	e84a                	sd	s2,16(sp)
      aa:	e44e                	sd	s3,8(sp)
      ac:	e052                	sd	s4,0(sp)
      ae:	1800                	addi	s0,sp,48
      b0:	892a                	mv	s2,a0
      b2:	02c00493          	li	s1,44
    int i = 22;
    while(1) {
        if(signo) printf("handler 2: %d\n", i*2);
        else printf("handler 2: %d\n", i*2+1);
      b6:	00001a17          	auipc	s4,0x1
      ba:	f82a0a13          	addi	s4,s4,-126 # 1038 <thread_kill+0x46>
        i++;
        if(i == 26) {
      be:	03400993          	li	s3,52
      c2:	a831                	j	de <s2+0x3e>
        if(signo) printf("handler 2: %d\n", i*2);
      c4:	85a6                	mv	a1,s1
      c6:	8552                	mv	a0,s4
      c8:	00001097          	auipc	ra,0x1
      cc:	932080e7          	jalr	-1742(ra) # 9fa <printf>
        if(i == 26) {
      d0:	2489                	addiw	s1,s1,2
      d2:	03348063          	beq	s1,s3,f2 <s2+0x52>
            return;
        }
        thread_yield();
      d6:	00001097          	auipc	ra,0x1
      da:	e42080e7          	jalr	-446(ra) # f18 <thread_yield>
        if(signo) printf("handler 2: %d\n", i*2);
      de:	fe0913e3          	bnez	s2,c4 <s2+0x24>
        else printf("handler 2: %d\n", i*2+1);
      e2:	0014859b          	addiw	a1,s1,1
      e6:	8552                	mv	a0,s4
      e8:	00001097          	auipc	ra,0x1
      ec:	912080e7          	jalr	-1774(ra) # 9fa <printf>
      f0:	b7c5                	j	d0 <s2+0x30>
    }
}
      f2:	70a2                	ld	ra,40(sp)
      f4:	7402                	ld	s0,32(sp)
      f6:	64e2                	ld	s1,24(sp)
      f8:	6942                	ld	s2,16(sp)
      fa:	69a2                	ld	s3,8(sp)
      fc:	6a02                	ld	s4,0(sp)
      fe:	6145                	addi	sp,sp,48
     100:	8082                	ret

0000000000000102 <f2>:
        thread_yield();
    }
}

void f2(void *arg)
{
     102:	7179                	addi	sp,sp,-48
     104:	f406                	sd	ra,40(sp)
     106:	f022                	sd	s0,32(sp)
     108:	ec26                	sd	s1,24(sp)
     10a:	e84a                	sd	s2,16(sp)
     10c:	e44e                	sd	s3,8(sp)
     10e:	e052                	sd	s4,0(sp)
     110:	1800                	addi	s0,sp,48
    int i = 0;
    while(1) {
        printf("thread 2: %d\n", i++);
     112:	4581                	li	a1,0
     114:	00001517          	auipc	a0,0x1
     118:	f3450513          	addi	a0,a0,-204 # 1048 <thread_kill+0x56>
     11c:	00001097          	auipc	ra,0x1
     120:	8de080e7          	jalr	-1826(ra) # 9fa <printf>
     124:	4485                	li	s1,1
     126:	00001a17          	auipc	s4,0x1
     12a:	f22a0a13          	addi	s4,s4,-222 # 1048 <thread_kill+0x56>
        if (i == 4) {
     12e:	4991                	li	s3,4
     130:	a011                	j	134 <f2+0x32>
        printf("thread 2: %d\n", i++);
     132:	84ca                	mv	s1,s2
            thread_exit();
        }
        thread_yield();
     134:	00001097          	auipc	ra,0x1
     138:	de4080e7          	jalr	-540(ra) # f18 <thread_yield>
        printf("thread 2: %d\n", i++);
     13c:	0014891b          	addiw	s2,s1,1
     140:	85a6                	mv	a1,s1
     142:	8552                	mv	a0,s4
     144:	00001097          	auipc	ra,0x1
     148:	8b6080e7          	jalr	-1866(ra) # 9fa <printf>
        if (i == 4) {
     14c:	ff3913e3          	bne	s2,s3,132 <f2+0x30>
            thread_exit();
     150:	00001097          	auipc	ra,0x1
     154:	ba8080e7          	jalr	-1112(ra) # cf8 <thread_exit>
     158:	bfe9                	j	132 <f2+0x30>

000000000000015a <f5>:
{
     15a:	7179                	addi	sp,sp,-48
     15c:	f406                	sd	ra,40(sp)
     15e:	f022                	sd	s0,32(sp)
     160:	ec26                	sd	s1,24(sp)
     162:	e84a                	sd	s2,16(sp)
     164:	e44e                	sd	s3,8(sp)
     166:	e052                	sd	s4,0(sp)
     168:	1800                	addi	s0,sp,48
    thread_register_handler(1, s5);
     16a:	00000597          	auipc	a1,0x0
     16e:	eda58593          	addi	a1,a1,-294 # 44 <s5>
     172:	4505                	li	a0,1
     174:	00001097          	auipc	ra,0x1
     178:	e62080e7          	jalr	-414(ra) # fd6 <thread_register_handler>
        printf("thread 5: %d\n", i++);
     17c:	45a9                	li	a1,10
     17e:	00001517          	auipc	a0,0x1
     182:	eda50513          	addi	a0,a0,-294 # 1058 <thread_kill+0x66>
     186:	00001097          	auipc	ra,0x1
     18a:	874080e7          	jalr	-1932(ra) # 9fa <printf>
     18e:	44ad                	li	s1,11
     190:	00001a17          	auipc	s4,0x1
     194:	ec8a0a13          	addi	s4,s4,-312 # 1058 <thread_kill+0x66>
        if (i == 17) {
     198:	49c5                	li	s3,17
     19a:	a011                	j	19e <f5+0x44>
        printf("thread 5: %d\n", i++);
     19c:	84ca                	mv	s1,s2
        thread_yield();
     19e:	00001097          	auipc	ra,0x1
     1a2:	d7a080e7          	jalr	-646(ra) # f18 <thread_yield>
        printf("thread 5: %d\n", i++);
     1a6:	0014891b          	addiw	s2,s1,1
     1aa:	85a6                	mv	a1,s1
     1ac:	8552                	mv	a0,s4
     1ae:	00001097          	auipc	ra,0x1
     1b2:	84c080e7          	jalr	-1972(ra) # 9fa <printf>
        if (i == 17) {
     1b6:	ff3913e3          	bne	s2,s3,19c <f5+0x42>
            thread_exit();
     1ba:	00001097          	auipc	ra,0x1
     1be:	b3e080e7          	jalr	-1218(ra) # cf8 <thread_exit>
     1c2:	bfe9                	j	19c <f5+0x42>

00000000000001c4 <f4>:
{
     1c4:	7179                	addi	sp,sp,-48
     1c6:	f406                	sd	ra,40(sp)
     1c8:	f022                	sd	s0,32(sp)
     1ca:	ec26                	sd	s1,24(sp)
     1cc:	e84a                	sd	s2,16(sp)
     1ce:	e44e                	sd	s3,8(sp)
     1d0:	e052                	sd	s4,0(sp)
     1d2:	1800                	addi	s0,sp,48
    thread_register_handler(0, s4);
     1d4:	00000597          	auipc	a1,0x0
     1d8:	e2c58593          	addi	a1,a1,-468 # 0 <s4>
     1dc:	4501                	li	a0,0
     1de:	00001097          	auipc	ra,0x1
     1e2:	df8080e7          	jalr	-520(ra) # fd6 <thread_register_handler>
        printf("thread 4: %d\n", i++);
     1e6:	3e800593          	li	a1,1000
     1ea:	00001517          	auipc	a0,0x1
     1ee:	e7e50513          	addi	a0,a0,-386 # 1068 <thread_kill+0x76>
     1f2:	00001097          	auipc	ra,0x1
     1f6:	808080e7          	jalr	-2040(ra) # 9fa <printf>
     1fa:	3e900493          	li	s1,1001
     1fe:	00001a17          	auipc	s4,0x1
     202:	e6aa0a13          	addi	s4,s4,-406 # 1068 <thread_kill+0x76>
        if (i == 1011) {
     206:	3f300993          	li	s3,1011
     20a:	a011                	j	20e <f4+0x4a>
        printf("thread 4: %d\n", i++);
     20c:	84ca                	mv	s1,s2
        thread_yield();
     20e:	00001097          	auipc	ra,0x1
     212:	d0a080e7          	jalr	-758(ra) # f18 <thread_yield>
        printf("thread 4: %d\n", i++);
     216:	0014891b          	addiw	s2,s1,1
     21a:	85a6                	mv	a1,s1
     21c:	8552                	mv	a0,s4
     21e:	00000097          	auipc	ra,0x0
     222:	7dc080e7          	jalr	2012(ra) # 9fa <printf>
        if (i == 1011) {
     226:	ff3913e3          	bne	s2,s3,20c <f4+0x48>
            thread_exit();
     22a:	00001097          	auipc	ra,0x1
     22e:	ace080e7          	jalr	-1330(ra) # cf8 <thread_exit>
     232:	bfe9                	j	20c <f4+0x48>

0000000000000234 <f3>:
{
     234:	715d                	addi	sp,sp,-80
     236:	e486                	sd	ra,72(sp)
     238:	e0a2                	sd	s0,64(sp)
     23a:	fc26                	sd	s1,56(sp)
     23c:	f84a                	sd	s2,48(sp)
     23e:	f44e                	sd	s3,40(sp)
     240:	f052                	sd	s4,32(sp)
     242:	ec56                	sd	s5,24(sp)
     244:	e85a                	sd	s6,16(sp)
     246:	e45e                	sd	s7,8(sp)
     248:	0880                	addi	s0,sp,80
    thread_register_handler(0, s3);
     24a:	00000597          	auipc	a1,0x0
     24e:	dd858593          	addi	a1,a1,-552 # 22 <s3>
     252:	4501                	li	a0,0
     254:	00001097          	auipc	ra,0x1
     258:	d82080e7          	jalr	-638(ra) # fd6 <thread_register_handler>
    struct thread *t4 = thread_create(f4, NULL);
     25c:	4581                	li	a1,0
     25e:	00000517          	auipc	a0,0x0
     262:	f6650513          	addi	a0,a0,-154 # 1c4 <f4>
     266:	00001097          	auipc	ra,0x1
     26a:	9ac080e7          	jalr	-1620(ra) # c12 <thread_create>
     26e:	8baa                	mv	s7,a0
    thread_add_runqueue(t4);
     270:	00001097          	auipc	ra,0x1
     274:	a36080e7          	jalr	-1482(ra) # ca6 <thread_add_runqueue>
    struct thread *t5 = thread_create(f5, NULL);
     278:	4581                	li	a1,0
     27a:	00000517          	auipc	a0,0x0
     27e:	ee050513          	addi	a0,a0,-288 # 15a <f5>
     282:	00001097          	auipc	ra,0x1
     286:	990080e7          	jalr	-1648(ra) # c12 <thread_create>
     28a:	8b2a                	mv	s6,a0
    thread_add_runqueue(t5);
     28c:	00001097          	auipc	ra,0x1
     290:	a1a080e7          	jalr	-1510(ra) # ca6 <thread_add_runqueue>
    int i = 10000;
     294:	6589                	lui	a1,0x2
     296:	71058593          	addi	a1,a1,1808 # 2710 <__global_pointer$+0xe3f>
        printf("thread 3: %d\n", i++);
     29a:	00001997          	auipc	s3,0x1
     29e:	dde98993          	addi	s3,s3,-546 # 1078 <thread_kill+0x86>
        if (i == 10003) {
     2a2:	6a89                	lui	s5,0x2
     2a4:	713a8913          	addi	s2,s5,1811 # 2713 <__global_pointer$+0xe42>
        if (i == 10004) {
     2a8:	714a8a13          	addi	s4,s5,1812
        if (i == 10006) {
     2ac:	716a8a93          	addi	s5,s5,1814
     2b0:	a805                	j	2e0 <f3+0xac>
            thread_kill(t4, 1);
     2b2:	4585                	li	a1,1
     2b4:	855e                	mv	a0,s7
     2b6:	00001097          	auipc	ra,0x1
     2ba:	d3c080e7          	jalr	-708(ra) # ff2 <thread_kill>
        if (i == 10006) {
     2be:	a821                	j	2d6 <f3+0xa2>
            thread_kill(t5, 1);
     2c0:	4585                	li	a1,1
     2c2:	855a                	mv	a0,s6
     2c4:	00001097          	auipc	ra,0x1
     2c8:	d2e080e7          	jalr	-722(ra) # ff2 <thread_kill>
        if (i == 10006) {
     2cc:	a029                	j	2d6 <f3+0xa2>
            thread_exit();
     2ce:	00001097          	auipc	ra,0x1
     2d2:	a2a080e7          	jalr	-1494(ra) # cf8 <thread_exit>
        thread_yield();
     2d6:	00001097          	auipc	ra,0x1
     2da:	c42080e7          	jalr	-958(ra) # f18 <thread_yield>
        printf("thread 3: %d\n", i++);
     2de:	85a6                	mv	a1,s1
     2e0:	0015849b          	addiw	s1,a1,1
     2e4:	854e                	mv	a0,s3
     2e6:	00000097          	auipc	ra,0x0
     2ea:	714080e7          	jalr	1812(ra) # 9fa <printf>
        if (i == 10003) {
     2ee:	fd2482e3          	beq	s1,s2,2b2 <f3+0x7e>
        if (i == 10004) {
     2f2:	fd4487e3          	beq	s1,s4,2c0 <f3+0x8c>
        if (i == 10006) {
     2f6:	fd548ce3          	beq	s1,s5,2ce <f3+0x9a>
     2fa:	bff1                	j	2d6 <f3+0xa2>

00000000000002fc <f1>:
    }
}

void f1(void *arg)
{
     2fc:	715d                	addi	sp,sp,-80
     2fe:	e486                	sd	ra,72(sp)
     300:	e0a2                	sd	s0,64(sp)
     302:	fc26                	sd	s1,56(sp)
     304:	f84a                	sd	s2,48(sp)
     306:	f44e                	sd	s3,40(sp)
     308:	f052                	sd	s4,32(sp)
     30a:	ec56                	sd	s5,24(sp)
     30c:	e85a                	sd	s6,16(sp)
     30e:	e45e                	sd	s7,8(sp)
     310:	0880                	addi	s0,sp,80
    thread_register_handler(0, s2);
     312:	00000597          	auipc	a1,0x0
     316:	d8e58593          	addi	a1,a1,-626 # a0 <s2>
     31a:	4501                	li	a0,0
     31c:	00001097          	auipc	ra,0x1
     320:	cba080e7          	jalr	-838(ra) # fd6 <thread_register_handler>
    int i = 100;

    struct thread *t2 = thread_create(f2, NULL);
     324:	4581                	li	a1,0
     326:	00000517          	auipc	a0,0x0
     32a:	ddc50513          	addi	a0,a0,-548 # 102 <f2>
     32e:	00001097          	auipc	ra,0x1
     332:	8e4080e7          	jalr	-1820(ra) # c12 <thread_create>
     336:	8baa                	mv	s7,a0
    thread_add_runqueue(t2);
     338:	00001097          	auipc	ra,0x1
     33c:	96e080e7          	jalr	-1682(ra) # ca6 <thread_add_runqueue>
    struct thread *t3 = thread_create(f3, NULL);
     340:	4581                	li	a1,0
     342:	00000517          	auipc	a0,0x0
     346:	ef250513          	addi	a0,a0,-270 # 234 <f3>
     34a:	00001097          	auipc	ra,0x1
     34e:	8c8080e7          	jalr	-1848(ra) # c12 <thread_create>
     352:	8b2a                	mv	s6,a0
    thread_add_runqueue(t3);
     354:	00001097          	auipc	ra,0x1
     358:	952080e7          	jalr	-1710(ra) # ca6 <thread_add_runqueue>
    int i = 100;
     35c:	06400593          	li	a1,100
    

    while(1) {
        printf("thread 1: %d\n", i++);
     360:	00001997          	auipc	s3,0x1
     364:	d2898993          	addi	s3,s3,-728 # 1088 <thread_kill+0x96>
        if (i == 101) {
     368:	06500913          	li	s2,101
            thread_kill(t2, 0);
        }
        if (i == 104) {
     36c:	06800a13          	li	s4,104
            thread_kill(t3, 0);
        }
        if (i == 105) {
     370:	06900a93          	li	s5,105
     374:	a805                	j	3a4 <f1+0xa8>
            thread_kill(t2, 0);
     376:	4581                	li	a1,0
     378:	855e                	mv	a0,s7
     37a:	00001097          	auipc	ra,0x1
     37e:	c78080e7          	jalr	-904(ra) # ff2 <thread_kill>
        if (i == 105) {
     382:	a821                	j	39a <f1+0x9e>
            thread_kill(t3, 0);
     384:	4581                	li	a1,0
     386:	855a                	mv	a0,s6
     388:	00001097          	auipc	ra,0x1
     38c:	c6a080e7          	jalr	-918(ra) # ff2 <thread_kill>
        if (i == 105) {
     390:	a029                	j	39a <f1+0x9e>
            thread_exit();
     392:	00001097          	auipc	ra,0x1
     396:	966080e7          	jalr	-1690(ra) # cf8 <thread_exit>
        }
        thread_yield();
     39a:	00001097          	auipc	ra,0x1
     39e:	b7e080e7          	jalr	-1154(ra) # f18 <thread_yield>
        printf("thread 1: %d\n", i++);
     3a2:	85a6                	mv	a1,s1
     3a4:	0015849b          	addiw	s1,a1,1
     3a8:	854e                	mv	a0,s3
     3aa:	00000097          	auipc	ra,0x0
     3ae:	650080e7          	jalr	1616(ra) # 9fa <printf>
        if (i == 101) {
     3b2:	fd2482e3          	beq	s1,s2,376 <f1+0x7a>
        if (i == 104) {
     3b6:	fd4487e3          	beq	s1,s4,384 <f1+0x88>
        if (i == 105) {
     3ba:	fd548ce3          	beq	s1,s5,392 <f1+0x96>
     3be:	bff1                	j	39a <f1+0x9e>

00000000000003c0 <main>:
    }
}

int main(int argc, char **argv)
{
     3c0:	1141                	addi	sp,sp,-16
     3c2:	e406                	sd	ra,8(sp)
     3c4:	e022                	sd	s0,0(sp)
     3c6:	0800                	addi	s0,sp,16
    printf("mp1-part2-2\n");
     3c8:	00001517          	auipc	a0,0x1
     3cc:	cd050513          	addi	a0,a0,-816 # 1098 <thread_kill+0xa6>
     3d0:	00000097          	auipc	ra,0x0
     3d4:	62a080e7          	jalr	1578(ra) # 9fa <printf>
    struct thread *t1 = thread_create(f1, NULL);
     3d8:	4581                	li	a1,0
     3da:	00000517          	auipc	a0,0x0
     3de:	f2250513          	addi	a0,a0,-222 # 2fc <f1>
     3e2:	00001097          	auipc	ra,0x1
     3e6:	830080e7          	jalr	-2000(ra) # c12 <thread_create>
    thread_add_runqueue(t1);
     3ea:	00001097          	auipc	ra,0x1
     3ee:	8bc080e7          	jalr	-1860(ra) # ca6 <thread_add_runqueue>
    thread_start_threading();
     3f2:	00001097          	auipc	ra,0x1
     3f6:	bb8080e7          	jalr	-1096(ra) # faa <thread_start_threading>
    printf("\nexited\n");
     3fa:	00001517          	auipc	a0,0x1
     3fe:	cae50513          	addi	a0,a0,-850 # 10a8 <thread_kill+0xb6>
     402:	00000097          	auipc	ra,0x0
     406:	5f8080e7          	jalr	1528(ra) # 9fa <printf>
    exit(0);
     40a:	4501                	li	a0,0
     40c:	00000097          	auipc	ra,0x0
     410:	276080e7          	jalr	630(ra) # 682 <exit>

0000000000000414 <strcpy>:
#include "kernel/fcntl.h"
#include "user/user.h"

char*
strcpy(char *s, const char *t)
{
     414:	1141                	addi	sp,sp,-16
     416:	e422                	sd	s0,8(sp)
     418:	0800                	addi	s0,sp,16
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
     41a:	87aa                	mv	a5,a0
     41c:	0585                	addi	a1,a1,1
     41e:	0785                	addi	a5,a5,1
     420:	fff5c703          	lbu	a4,-1(a1)
     424:	fee78fa3          	sb	a4,-1(a5)
     428:	fb75                	bnez	a4,41c <strcpy+0x8>
    ;
  return os;
}
     42a:	6422                	ld	s0,8(sp)
     42c:	0141                	addi	sp,sp,16
     42e:	8082                	ret

0000000000000430 <strcmp>:

int
strcmp(const char *p, const char *q)
{
     430:	1141                	addi	sp,sp,-16
     432:	e422                	sd	s0,8(sp)
     434:	0800                	addi	s0,sp,16
  while(*p && *p == *q)
     436:	00054783          	lbu	a5,0(a0)
     43a:	cb91                	beqz	a5,44e <strcmp+0x1e>
     43c:	0005c703          	lbu	a4,0(a1)
     440:	00f71763          	bne	a4,a5,44e <strcmp+0x1e>
    p++, q++;
     444:	0505                	addi	a0,a0,1
     446:	0585                	addi	a1,a1,1
  while(*p && *p == *q)
     448:	00054783          	lbu	a5,0(a0)
     44c:	fbe5                	bnez	a5,43c <strcmp+0xc>
  return (uchar)*p - (uchar)*q;
     44e:	0005c503          	lbu	a0,0(a1)
}
     452:	40a7853b          	subw	a0,a5,a0
     456:	6422                	ld	s0,8(sp)
     458:	0141                	addi	sp,sp,16
     45a:	8082                	ret

000000000000045c <strlen>:

uint
strlen(const char *s)
{
     45c:	1141                	addi	sp,sp,-16
     45e:	e422                	sd	s0,8(sp)
     460:	0800                	addi	s0,sp,16
  int n;

  for(n = 0; s[n]; n++)
     462:	00054783          	lbu	a5,0(a0)
     466:	cf91                	beqz	a5,482 <strlen+0x26>
     468:	0505                	addi	a0,a0,1
     46a:	87aa                	mv	a5,a0
     46c:	4685                	li	a3,1
     46e:	9e89                	subw	a3,a3,a0
     470:	00f6853b          	addw	a0,a3,a5
     474:	0785                	addi	a5,a5,1
     476:	fff7c703          	lbu	a4,-1(a5)
     47a:	fb7d                	bnez	a4,470 <strlen+0x14>
    ;
  return n;
}
     47c:	6422                	ld	s0,8(sp)
     47e:	0141                	addi	sp,sp,16
     480:	8082                	ret
  for(n = 0; s[n]; n++)
     482:	4501                	li	a0,0
     484:	bfe5                	j	47c <strlen+0x20>

0000000000000486 <memset>:

void*
memset(void *dst, int c, uint n)
{
     486:	1141                	addi	sp,sp,-16
     488:	e422                	sd	s0,8(sp)
     48a:	0800                	addi	s0,sp,16
  char *cdst = (char *) dst;
  int i;
  for(i = 0; i < n; i++){
     48c:	ca19                	beqz	a2,4a2 <memset+0x1c>
     48e:	87aa                	mv	a5,a0
     490:	1602                	slli	a2,a2,0x20
     492:	9201                	srli	a2,a2,0x20
     494:	00a60733          	add	a4,a2,a0
    cdst[i] = c;
     498:	00b78023          	sb	a1,0(a5)
  for(i = 0; i < n; i++){
     49c:	0785                	addi	a5,a5,1
     49e:	fee79de3          	bne	a5,a4,498 <memset+0x12>
  }
  return dst;
}
     4a2:	6422                	ld	s0,8(sp)
     4a4:	0141                	addi	sp,sp,16
     4a6:	8082                	ret

00000000000004a8 <strchr>:

char*
strchr(const char *s, char c)
{
     4a8:	1141                	addi	sp,sp,-16
     4aa:	e422                	sd	s0,8(sp)
     4ac:	0800                	addi	s0,sp,16
  for(; *s; s++)
     4ae:	00054783          	lbu	a5,0(a0)
     4b2:	cb99                	beqz	a5,4c8 <strchr+0x20>
    if(*s == c)
     4b4:	00f58763          	beq	a1,a5,4c2 <strchr+0x1a>
  for(; *s; s++)
     4b8:	0505                	addi	a0,a0,1
     4ba:	00054783          	lbu	a5,0(a0)
     4be:	fbfd                	bnez	a5,4b4 <strchr+0xc>
      return (char*)s;
  return 0;
     4c0:	4501                	li	a0,0
}
     4c2:	6422                	ld	s0,8(sp)
     4c4:	0141                	addi	sp,sp,16
     4c6:	8082                	ret
  return 0;
     4c8:	4501                	li	a0,0
     4ca:	bfe5                	j	4c2 <strchr+0x1a>

00000000000004cc <gets>:

char*
gets(char *buf, int max)
{
     4cc:	711d                	addi	sp,sp,-96
     4ce:	ec86                	sd	ra,88(sp)
     4d0:	e8a2                	sd	s0,80(sp)
     4d2:	e4a6                	sd	s1,72(sp)
     4d4:	e0ca                	sd	s2,64(sp)
     4d6:	fc4e                	sd	s3,56(sp)
     4d8:	f852                	sd	s4,48(sp)
     4da:	f456                	sd	s5,40(sp)
     4dc:	f05a                	sd	s6,32(sp)
     4de:	ec5e                	sd	s7,24(sp)
     4e0:	1080                	addi	s0,sp,96
     4e2:	8baa                	mv	s7,a0
     4e4:	8a2e                	mv	s4,a1
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
     4e6:	892a                	mv	s2,a0
     4e8:	4481                	li	s1,0
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
     4ea:	4aa9                	li	s5,10
     4ec:	4b35                	li	s6,13
  for(i=0; i+1 < max; ){
     4ee:	89a6                	mv	s3,s1
     4f0:	2485                	addiw	s1,s1,1
     4f2:	0344d863          	bge	s1,s4,522 <gets+0x56>
    cc = read(0, &c, 1);
     4f6:	4605                	li	a2,1
     4f8:	faf40593          	addi	a1,s0,-81
     4fc:	4501                	li	a0,0
     4fe:	00000097          	auipc	ra,0x0
     502:	19c080e7          	jalr	412(ra) # 69a <read>
    if(cc < 1)
     506:	00a05e63          	blez	a0,522 <gets+0x56>
    buf[i++] = c;
     50a:	faf44783          	lbu	a5,-81(s0)
     50e:	00f90023          	sb	a5,0(s2)
    if(c == '\n' || c == '\r')
     512:	01578763          	beq	a5,s5,520 <gets+0x54>
     516:	0905                	addi	s2,s2,1
     518:	fd679be3          	bne	a5,s6,4ee <gets+0x22>
  for(i=0; i+1 < max; ){
     51c:	89a6                	mv	s3,s1
     51e:	a011                	j	522 <gets+0x56>
     520:	89a6                	mv	s3,s1
      break;
  }
  buf[i] = '\0';
     522:	99de                	add	s3,s3,s7
     524:	00098023          	sb	zero,0(s3)
  return buf;
}
     528:	855e                	mv	a0,s7
     52a:	60e6                	ld	ra,88(sp)
     52c:	6446                	ld	s0,80(sp)
     52e:	64a6                	ld	s1,72(sp)
     530:	6906                	ld	s2,64(sp)
     532:	79e2                	ld	s3,56(sp)
     534:	7a42                	ld	s4,48(sp)
     536:	7aa2                	ld	s5,40(sp)
     538:	7b02                	ld	s6,32(sp)
     53a:	6be2                	ld	s7,24(sp)
     53c:	6125                	addi	sp,sp,96
     53e:	8082                	ret

0000000000000540 <stat>:

int
stat(const char *n, struct stat *st)
{
     540:	1101                	addi	sp,sp,-32
     542:	ec06                	sd	ra,24(sp)
     544:	e822                	sd	s0,16(sp)
     546:	e426                	sd	s1,8(sp)
     548:	e04a                	sd	s2,0(sp)
     54a:	1000                	addi	s0,sp,32
     54c:	892e                	mv	s2,a1
  int fd;
  int r;

  fd = open(n, O_RDONLY);
     54e:	4581                	li	a1,0
     550:	00000097          	auipc	ra,0x0
     554:	172080e7          	jalr	370(ra) # 6c2 <open>
  if(fd < 0)
     558:	02054563          	bltz	a0,582 <stat+0x42>
     55c:	84aa                	mv	s1,a0
    return -1;
  r = fstat(fd, st);
     55e:	85ca                	mv	a1,s2
     560:	00000097          	auipc	ra,0x0
     564:	17a080e7          	jalr	378(ra) # 6da <fstat>
     568:	892a                	mv	s2,a0
  close(fd);
     56a:	8526                	mv	a0,s1
     56c:	00000097          	auipc	ra,0x0
     570:	13e080e7          	jalr	318(ra) # 6aa <close>
  return r;
}
     574:	854a                	mv	a0,s2
     576:	60e2                	ld	ra,24(sp)
     578:	6442                	ld	s0,16(sp)
     57a:	64a2                	ld	s1,8(sp)
     57c:	6902                	ld	s2,0(sp)
     57e:	6105                	addi	sp,sp,32
     580:	8082                	ret
    return -1;
     582:	597d                	li	s2,-1
     584:	bfc5                	j	574 <stat+0x34>

0000000000000586 <atoi>:

int
atoi(const char *s)
{
     586:	1141                	addi	sp,sp,-16
     588:	e422                	sd	s0,8(sp)
     58a:	0800                	addi	s0,sp,16
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
     58c:	00054603          	lbu	a2,0(a0)
     590:	fd06079b          	addiw	a5,a2,-48
     594:	0ff7f793          	andi	a5,a5,255
     598:	4725                	li	a4,9
     59a:	02f76963          	bltu	a4,a5,5cc <atoi+0x46>
     59e:	86aa                	mv	a3,a0
  n = 0;
     5a0:	4501                	li	a0,0
  while('0' <= *s && *s <= '9')
     5a2:	45a5                	li	a1,9
    n = n*10 + *s++ - '0';
     5a4:	0685                	addi	a3,a3,1
     5a6:	0025179b          	slliw	a5,a0,0x2
     5aa:	9fa9                	addw	a5,a5,a0
     5ac:	0017979b          	slliw	a5,a5,0x1
     5b0:	9fb1                	addw	a5,a5,a2
     5b2:	fd07851b          	addiw	a0,a5,-48
  while('0' <= *s && *s <= '9')
     5b6:	0006c603          	lbu	a2,0(a3)
     5ba:	fd06071b          	addiw	a4,a2,-48
     5be:	0ff77713          	andi	a4,a4,255
     5c2:	fee5f1e3          	bgeu	a1,a4,5a4 <atoi+0x1e>
  return n;
}
     5c6:	6422                	ld	s0,8(sp)
     5c8:	0141                	addi	sp,sp,16
     5ca:	8082                	ret
  n = 0;
     5cc:	4501                	li	a0,0
     5ce:	bfe5                	j	5c6 <atoi+0x40>

00000000000005d0 <memmove>:

void*
memmove(void *vdst, const void *vsrc, int n)
{
     5d0:	1141                	addi	sp,sp,-16
     5d2:	e422                	sd	s0,8(sp)
     5d4:	0800                	addi	s0,sp,16
  char *dst;
  const char *src;

  dst = vdst;
  src = vsrc;
  if (src > dst) {
     5d6:	02b57463          	bgeu	a0,a1,5fe <memmove+0x2e>
    while(n-- > 0)
     5da:	00c05f63          	blez	a2,5f8 <memmove+0x28>
     5de:	1602                	slli	a2,a2,0x20
     5e0:	9201                	srli	a2,a2,0x20
     5e2:	00c507b3          	add	a5,a0,a2
  dst = vdst;
     5e6:	872a                	mv	a4,a0
      *dst++ = *src++;
     5e8:	0585                	addi	a1,a1,1
     5ea:	0705                	addi	a4,a4,1
     5ec:	fff5c683          	lbu	a3,-1(a1)
     5f0:	fed70fa3          	sb	a3,-1(a4)
    while(n-- > 0)
     5f4:	fee79ae3          	bne	a5,a4,5e8 <memmove+0x18>
    src += n;
    while(n-- > 0)
      *--dst = *--src;
  }
  return vdst;
}
     5f8:	6422                	ld	s0,8(sp)
     5fa:	0141                	addi	sp,sp,16
     5fc:	8082                	ret
    dst += n;
     5fe:	00c50733          	add	a4,a0,a2
    src += n;
     602:	95b2                	add	a1,a1,a2
    while(n-- > 0)
     604:	fec05ae3          	blez	a2,5f8 <memmove+0x28>
     608:	fff6079b          	addiw	a5,a2,-1
     60c:	1782                	slli	a5,a5,0x20
     60e:	9381                	srli	a5,a5,0x20
     610:	fff7c793          	not	a5,a5
     614:	97ba                	add	a5,a5,a4
      *--dst = *--src;
     616:	15fd                	addi	a1,a1,-1
     618:	177d                	addi	a4,a4,-1
     61a:	0005c683          	lbu	a3,0(a1)
     61e:	00d70023          	sb	a3,0(a4)
    while(n-- > 0)
     622:	fee79ae3          	bne	a5,a4,616 <memmove+0x46>
     626:	bfc9                	j	5f8 <memmove+0x28>

0000000000000628 <memcmp>:

int
memcmp(const void *s1, const void *s2, uint n)
{
     628:	1141                	addi	sp,sp,-16
     62a:	e422                	sd	s0,8(sp)
     62c:	0800                	addi	s0,sp,16
  const char *p1 = s1, *p2 = s2;
  while (n-- > 0) {
     62e:	ca05                	beqz	a2,65e <memcmp+0x36>
     630:	fff6069b          	addiw	a3,a2,-1
     634:	1682                	slli	a3,a3,0x20
     636:	9281                	srli	a3,a3,0x20
     638:	0685                	addi	a3,a3,1
     63a:	96aa                	add	a3,a3,a0
    if (*p1 != *p2) {
     63c:	00054783          	lbu	a5,0(a0)
     640:	0005c703          	lbu	a4,0(a1)
     644:	00e79863          	bne	a5,a4,654 <memcmp+0x2c>
      return *p1 - *p2;
    }
    p1++;
     648:	0505                	addi	a0,a0,1
    p2++;
     64a:	0585                	addi	a1,a1,1
  while (n-- > 0) {
     64c:	fed518e3          	bne	a0,a3,63c <memcmp+0x14>
  }
  return 0;
     650:	4501                	li	a0,0
     652:	a019                	j	658 <memcmp+0x30>
      return *p1 - *p2;
     654:	40e7853b          	subw	a0,a5,a4
}
     658:	6422                	ld	s0,8(sp)
     65a:	0141                	addi	sp,sp,16
     65c:	8082                	ret
  return 0;
     65e:	4501                	li	a0,0
     660:	bfe5                	j	658 <memcmp+0x30>

0000000000000662 <memcpy>:

void *
memcpy(void *dst, const void *src, uint n)
{
     662:	1141                	addi	sp,sp,-16
     664:	e406                	sd	ra,8(sp)
     666:	e022                	sd	s0,0(sp)
     668:	0800                	addi	s0,sp,16
  return memmove(dst, src, n);
     66a:	00000097          	auipc	ra,0x0
     66e:	f66080e7          	jalr	-154(ra) # 5d0 <memmove>
}
     672:	60a2                	ld	ra,8(sp)
     674:	6402                	ld	s0,0(sp)
     676:	0141                	addi	sp,sp,16
     678:	8082                	ret

000000000000067a <fork>:
# generated by usys.pl - do not edit
#include "kernel/syscall.h"
.global fork
fork:
 li a7, SYS_fork
     67a:	4885                	li	a7,1
 ecall
     67c:	00000073          	ecall
 ret
     680:	8082                	ret

0000000000000682 <exit>:
.global exit
exit:
 li a7, SYS_exit
     682:	4889                	li	a7,2
 ecall
     684:	00000073          	ecall
 ret
     688:	8082                	ret

000000000000068a <wait>:
.global wait
wait:
 li a7, SYS_wait
     68a:	488d                	li	a7,3
 ecall
     68c:	00000073          	ecall
 ret
     690:	8082                	ret

0000000000000692 <pipe>:
.global pipe
pipe:
 li a7, SYS_pipe
     692:	4891                	li	a7,4
 ecall
     694:	00000073          	ecall
 ret
     698:	8082                	ret

000000000000069a <read>:
.global read
read:
 li a7, SYS_read
     69a:	4895                	li	a7,5
 ecall
     69c:	00000073          	ecall
 ret
     6a0:	8082                	ret

00000000000006a2 <write>:
.global write
write:
 li a7, SYS_write
     6a2:	48c1                	li	a7,16
 ecall
     6a4:	00000073          	ecall
 ret
     6a8:	8082                	ret

00000000000006aa <close>:
.global close
close:
 li a7, SYS_close
     6aa:	48d5                	li	a7,21
 ecall
     6ac:	00000073          	ecall
 ret
     6b0:	8082                	ret

00000000000006b2 <kill>:
.global kill
kill:
 li a7, SYS_kill
     6b2:	4899                	li	a7,6
 ecall
     6b4:	00000073          	ecall
 ret
     6b8:	8082                	ret

00000000000006ba <exec>:
.global exec
exec:
 li a7, SYS_exec
     6ba:	489d                	li	a7,7
 ecall
     6bc:	00000073          	ecall
 ret
     6c0:	8082                	ret

00000000000006c2 <open>:
.global open
open:
 li a7, SYS_open
     6c2:	48bd                	li	a7,15
 ecall
     6c4:	00000073          	ecall
 ret
     6c8:	8082                	ret

00000000000006ca <mknod>:
.global mknod
mknod:
 li a7, SYS_mknod
     6ca:	48c5                	li	a7,17
 ecall
     6cc:	00000073          	ecall
 ret
     6d0:	8082                	ret

00000000000006d2 <unlink>:
.global unlink
unlink:
 li a7, SYS_unlink
     6d2:	48c9                	li	a7,18
 ecall
     6d4:	00000073          	ecall
 ret
     6d8:	8082                	ret

00000000000006da <fstat>:
.global fstat
fstat:
 li a7, SYS_fstat
     6da:	48a1                	li	a7,8
 ecall
     6dc:	00000073          	ecall
 ret
     6e0:	8082                	ret

00000000000006e2 <link>:
.global link
link:
 li a7, SYS_link
     6e2:	48cd                	li	a7,19
 ecall
     6e4:	00000073          	ecall
 ret
     6e8:	8082                	ret

00000000000006ea <mkdir>:
.global mkdir
mkdir:
 li a7, SYS_mkdir
     6ea:	48d1                	li	a7,20
 ecall
     6ec:	00000073          	ecall
 ret
     6f0:	8082                	ret

00000000000006f2 <chdir>:
.global chdir
chdir:
 li a7, SYS_chdir
     6f2:	48a5                	li	a7,9
 ecall
     6f4:	00000073          	ecall
 ret
     6f8:	8082                	ret

00000000000006fa <dup>:
.global dup
dup:
 li a7, SYS_dup
     6fa:	48a9                	li	a7,10
 ecall
     6fc:	00000073          	ecall
 ret
     700:	8082                	ret

0000000000000702 <getpid>:
.global getpid
getpid:
 li a7, SYS_getpid
     702:	48ad                	li	a7,11
 ecall
     704:	00000073          	ecall
 ret
     708:	8082                	ret

000000000000070a <sbrk>:
.global sbrk
sbrk:
 li a7, SYS_sbrk
     70a:	48b1                	li	a7,12
 ecall
     70c:	00000073          	ecall
 ret
     710:	8082                	ret

0000000000000712 <sleep>:
.global sleep
sleep:
 li a7, SYS_sleep
     712:	48b5                	li	a7,13
 ecall
     714:	00000073          	ecall
 ret
     718:	8082                	ret

000000000000071a <uptime>:
.global uptime
uptime:
 li a7, SYS_uptime
     71a:	48b9                	li	a7,14
 ecall
     71c:	00000073          	ecall
 ret
     720:	8082                	ret

0000000000000722 <putc>:

static char digits[] = "0123456789ABCDEF";

static void
putc(int fd, char c)
{
     722:	1101                	addi	sp,sp,-32
     724:	ec06                	sd	ra,24(sp)
     726:	e822                	sd	s0,16(sp)
     728:	1000                	addi	s0,sp,32
     72a:	feb407a3          	sb	a1,-17(s0)
  write(fd, &c, 1);
     72e:	4605                	li	a2,1
     730:	fef40593          	addi	a1,s0,-17
     734:	00000097          	auipc	ra,0x0
     738:	f6e080e7          	jalr	-146(ra) # 6a2 <write>
}
     73c:	60e2                	ld	ra,24(sp)
     73e:	6442                	ld	s0,16(sp)
     740:	6105                	addi	sp,sp,32
     742:	8082                	ret

0000000000000744 <printint>:

static void
printint(int fd, int xx, int base, int sgn)
{
     744:	7139                	addi	sp,sp,-64
     746:	fc06                	sd	ra,56(sp)
     748:	f822                	sd	s0,48(sp)
     74a:	f426                	sd	s1,40(sp)
     74c:	f04a                	sd	s2,32(sp)
     74e:	ec4e                	sd	s3,24(sp)
     750:	0080                	addi	s0,sp,64
     752:	84aa                	mv	s1,a0
  char buf[16];
  int i, neg;
  uint x;

  neg = 0;
  if(sgn && xx < 0){
     754:	c299                	beqz	a3,75a <printint+0x16>
     756:	0805c863          	bltz	a1,7e6 <printint+0xa2>
    neg = 1;
    x = -xx;
  } else {
    x = xx;
     75a:	2581                	sext.w	a1,a1
  neg = 0;
     75c:	4881                	li	a7,0
     75e:	fc040693          	addi	a3,s0,-64
  }

  i = 0;
     762:	4701                	li	a4,0
  do{
    buf[i++] = digits[x % base];
     764:	2601                	sext.w	a2,a2
     766:	00001517          	auipc	a0,0x1
     76a:	95a50513          	addi	a0,a0,-1702 # 10c0 <digits>
     76e:	883a                	mv	a6,a4
     770:	2705                	addiw	a4,a4,1
     772:	02c5f7bb          	remuw	a5,a1,a2
     776:	1782                	slli	a5,a5,0x20
     778:	9381                	srli	a5,a5,0x20
     77a:	97aa                	add	a5,a5,a0
     77c:	0007c783          	lbu	a5,0(a5)
     780:	00f68023          	sb	a5,0(a3)
  }while((x /= base) != 0);
     784:	0005879b          	sext.w	a5,a1
     788:	02c5d5bb          	divuw	a1,a1,a2
     78c:	0685                	addi	a3,a3,1
     78e:	fec7f0e3          	bgeu	a5,a2,76e <printint+0x2a>
  if(neg)
     792:	00088b63          	beqz	a7,7a8 <printint+0x64>
    buf[i++] = '-';
     796:	fd040793          	addi	a5,s0,-48
     79a:	973e                	add	a4,a4,a5
     79c:	02d00793          	li	a5,45
     7a0:	fef70823          	sb	a5,-16(a4)
     7a4:	0028071b          	addiw	a4,a6,2

  while(--i >= 0)
     7a8:	02e05863          	blez	a4,7d8 <printint+0x94>
     7ac:	fc040793          	addi	a5,s0,-64
     7b0:	00e78933          	add	s2,a5,a4
     7b4:	fff78993          	addi	s3,a5,-1
     7b8:	99ba                	add	s3,s3,a4
     7ba:	377d                	addiw	a4,a4,-1
     7bc:	1702                	slli	a4,a4,0x20
     7be:	9301                	srli	a4,a4,0x20
     7c0:	40e989b3          	sub	s3,s3,a4
    putc(fd, buf[i]);
     7c4:	fff94583          	lbu	a1,-1(s2)
     7c8:	8526                	mv	a0,s1
     7ca:	00000097          	auipc	ra,0x0
     7ce:	f58080e7          	jalr	-168(ra) # 722 <putc>
  while(--i >= 0)
     7d2:	197d                	addi	s2,s2,-1
     7d4:	ff3918e3          	bne	s2,s3,7c4 <printint+0x80>
}
     7d8:	70e2                	ld	ra,56(sp)
     7da:	7442                	ld	s0,48(sp)
     7dc:	74a2                	ld	s1,40(sp)
     7de:	7902                	ld	s2,32(sp)
     7e0:	69e2                	ld	s3,24(sp)
     7e2:	6121                	addi	sp,sp,64
     7e4:	8082                	ret
    x = -xx;
     7e6:	40b005bb          	negw	a1,a1
    neg = 1;
     7ea:	4885                	li	a7,1
    x = -xx;
     7ec:	bf8d                	j	75e <printint+0x1a>

00000000000007ee <vprintf>:
}

// Print to the given fd. Only understands %d, %x, %p, %s.
void
vprintf(int fd, const char *fmt, va_list ap)
{
     7ee:	7119                	addi	sp,sp,-128
     7f0:	fc86                	sd	ra,120(sp)
     7f2:	f8a2                	sd	s0,112(sp)
     7f4:	f4a6                	sd	s1,104(sp)
     7f6:	f0ca                	sd	s2,96(sp)
     7f8:	ecce                	sd	s3,88(sp)
     7fa:	e8d2                	sd	s4,80(sp)
     7fc:	e4d6                	sd	s5,72(sp)
     7fe:	e0da                	sd	s6,64(sp)
     800:	fc5e                	sd	s7,56(sp)
     802:	f862                	sd	s8,48(sp)
     804:	f466                	sd	s9,40(sp)
     806:	f06a                	sd	s10,32(sp)
     808:	ec6e                	sd	s11,24(sp)
     80a:	0100                	addi	s0,sp,128
  char *s;
  int c, i, state;

  state = 0;
  for(i = 0; fmt[i]; i++){
     80c:	0005c903          	lbu	s2,0(a1)
     810:	18090f63          	beqz	s2,9ae <vprintf+0x1c0>
     814:	8aaa                	mv	s5,a0
     816:	8b32                	mv	s6,a2
     818:	00158493          	addi	s1,a1,1
  state = 0;
     81c:	4981                	li	s3,0
      if(c == '%'){
        state = '%';
      } else {
        putc(fd, c);
      }
    } else if(state == '%'){
     81e:	02500a13          	li	s4,37
      if(c == 'd'){
     822:	06400c13          	li	s8,100
        printint(fd, va_arg(ap, int), 10, 1);
      } else if(c == 'l') {
     826:	06c00c93          	li	s9,108
        printint(fd, va_arg(ap, uint64), 10, 0);
      } else if(c == 'x') {
     82a:	07800d13          	li	s10,120
        printint(fd, va_arg(ap, int), 16, 0);
      } else if(c == 'p') {
     82e:	07000d93          	li	s11,112
    putc(fd, digits[x >> (sizeof(uint64) * 8 - 4)]);
     832:	00001b97          	auipc	s7,0x1
     836:	88eb8b93          	addi	s7,s7,-1906 # 10c0 <digits>
     83a:	a839                	j	858 <vprintf+0x6a>
        putc(fd, c);
     83c:	85ca                	mv	a1,s2
     83e:	8556                	mv	a0,s5
     840:	00000097          	auipc	ra,0x0
     844:	ee2080e7          	jalr	-286(ra) # 722 <putc>
     848:	a019                	j	84e <vprintf+0x60>
    } else if(state == '%'){
     84a:	01498f63          	beq	s3,s4,868 <vprintf+0x7a>
  for(i = 0; fmt[i]; i++){
     84e:	0485                	addi	s1,s1,1
     850:	fff4c903          	lbu	s2,-1(s1)
     854:	14090d63          	beqz	s2,9ae <vprintf+0x1c0>
    c = fmt[i] & 0xff;
     858:	0009079b          	sext.w	a5,s2
    if(state == 0){
     85c:	fe0997e3          	bnez	s3,84a <vprintf+0x5c>
      if(c == '%'){
     860:	fd479ee3          	bne	a5,s4,83c <vprintf+0x4e>
        state = '%';
     864:	89be                	mv	s3,a5
     866:	b7e5                	j	84e <vprintf+0x60>
      if(c == 'd'){
     868:	05878063          	beq	a5,s8,8a8 <vprintf+0xba>
      } else if(c == 'l') {
     86c:	05978c63          	beq	a5,s9,8c4 <vprintf+0xd6>
      } else if(c == 'x') {
     870:	07a78863          	beq	a5,s10,8e0 <vprintf+0xf2>
      } else if(c == 'p') {
     874:	09b78463          	beq	a5,s11,8fc <vprintf+0x10e>
        printptr(fd, va_arg(ap, uint64));
      } else if(c == 's'){
     878:	07300713          	li	a4,115
     87c:	0ce78663          	beq	a5,a4,948 <vprintf+0x15a>
          s = "(null)";
        while(*s != 0){
          putc(fd, *s);
          s++;
        }
      } else if(c == 'c'){
     880:	06300713          	li	a4,99
     884:	0ee78e63          	beq	a5,a4,980 <vprintf+0x192>
        putc(fd, va_arg(ap, uint));
      } else if(c == '%'){
     888:	11478863          	beq	a5,s4,998 <vprintf+0x1aa>
        putc(fd, c);
      } else {
        // Unknown % sequence.  Print it to draw attention.
        putc(fd, '%');
     88c:	85d2                	mv	a1,s4
     88e:	8556                	mv	a0,s5
     890:	00000097          	auipc	ra,0x0
     894:	e92080e7          	jalr	-366(ra) # 722 <putc>
        putc(fd, c);
     898:	85ca                	mv	a1,s2
     89a:	8556                	mv	a0,s5
     89c:	00000097          	auipc	ra,0x0
     8a0:	e86080e7          	jalr	-378(ra) # 722 <putc>
      }
      state = 0;
     8a4:	4981                	li	s3,0
     8a6:	b765                	j	84e <vprintf+0x60>
        printint(fd, va_arg(ap, int), 10, 1);
     8a8:	008b0913          	addi	s2,s6,8
     8ac:	4685                	li	a3,1
     8ae:	4629                	li	a2,10
     8b0:	000b2583          	lw	a1,0(s6)
     8b4:	8556                	mv	a0,s5
     8b6:	00000097          	auipc	ra,0x0
     8ba:	e8e080e7          	jalr	-370(ra) # 744 <printint>
     8be:	8b4a                	mv	s6,s2
      state = 0;
     8c0:	4981                	li	s3,0
     8c2:	b771                	j	84e <vprintf+0x60>
        printint(fd, va_arg(ap, uint64), 10, 0);
     8c4:	008b0913          	addi	s2,s6,8
     8c8:	4681                	li	a3,0
     8ca:	4629                	li	a2,10
     8cc:	000b2583          	lw	a1,0(s6)
     8d0:	8556                	mv	a0,s5
     8d2:	00000097          	auipc	ra,0x0
     8d6:	e72080e7          	jalr	-398(ra) # 744 <printint>
     8da:	8b4a                	mv	s6,s2
      state = 0;
     8dc:	4981                	li	s3,0
     8de:	bf85                	j	84e <vprintf+0x60>
        printint(fd, va_arg(ap, int), 16, 0);
     8e0:	008b0913          	addi	s2,s6,8
     8e4:	4681                	li	a3,0
     8e6:	4641                	li	a2,16
     8e8:	000b2583          	lw	a1,0(s6)
     8ec:	8556                	mv	a0,s5
     8ee:	00000097          	auipc	ra,0x0
     8f2:	e56080e7          	jalr	-426(ra) # 744 <printint>
     8f6:	8b4a                	mv	s6,s2
      state = 0;
     8f8:	4981                	li	s3,0
     8fa:	bf91                	j	84e <vprintf+0x60>
        printptr(fd, va_arg(ap, uint64));
     8fc:	008b0793          	addi	a5,s6,8
     900:	f8f43423          	sd	a5,-120(s0)
     904:	000b3983          	ld	s3,0(s6)
  putc(fd, '0');
     908:	03000593          	li	a1,48
     90c:	8556                	mv	a0,s5
     90e:	00000097          	auipc	ra,0x0
     912:	e14080e7          	jalr	-492(ra) # 722 <putc>
  putc(fd, 'x');
     916:	85ea                	mv	a1,s10
     918:	8556                	mv	a0,s5
     91a:	00000097          	auipc	ra,0x0
     91e:	e08080e7          	jalr	-504(ra) # 722 <putc>
     922:	4941                	li	s2,16
    putc(fd, digits[x >> (sizeof(uint64) * 8 - 4)]);
     924:	03c9d793          	srli	a5,s3,0x3c
     928:	97de                	add	a5,a5,s7
     92a:	0007c583          	lbu	a1,0(a5)
     92e:	8556                	mv	a0,s5
     930:	00000097          	auipc	ra,0x0
     934:	df2080e7          	jalr	-526(ra) # 722 <putc>
  for (i = 0; i < (sizeof(uint64) * 2); i++, x <<= 4)
     938:	0992                	slli	s3,s3,0x4
     93a:	397d                	addiw	s2,s2,-1
     93c:	fe0914e3          	bnez	s2,924 <vprintf+0x136>
        printptr(fd, va_arg(ap, uint64));
     940:	f8843b03          	ld	s6,-120(s0)
      state = 0;
     944:	4981                	li	s3,0
     946:	b721                	j	84e <vprintf+0x60>
        s = va_arg(ap, char*);
     948:	008b0993          	addi	s3,s6,8
     94c:	000b3903          	ld	s2,0(s6)
        if(s == 0)
     950:	02090163          	beqz	s2,972 <vprintf+0x184>
        while(*s != 0){
     954:	00094583          	lbu	a1,0(s2)
     958:	c9a1                	beqz	a1,9a8 <vprintf+0x1ba>
          putc(fd, *s);
     95a:	8556                	mv	a0,s5
     95c:	00000097          	auipc	ra,0x0
     960:	dc6080e7          	jalr	-570(ra) # 722 <putc>
          s++;
     964:	0905                	addi	s2,s2,1
        while(*s != 0){
     966:	00094583          	lbu	a1,0(s2)
     96a:	f9e5                	bnez	a1,95a <vprintf+0x16c>
        s = va_arg(ap, char*);
     96c:	8b4e                	mv	s6,s3
      state = 0;
     96e:	4981                	li	s3,0
     970:	bdf9                	j	84e <vprintf+0x60>
          s = "(null)";
     972:	00000917          	auipc	s2,0x0
     976:	74690913          	addi	s2,s2,1862 # 10b8 <thread_kill+0xc6>
        while(*s != 0){
     97a:	02800593          	li	a1,40
     97e:	bff1                	j	95a <vprintf+0x16c>
        putc(fd, va_arg(ap, uint));
     980:	008b0913          	addi	s2,s6,8
     984:	000b4583          	lbu	a1,0(s6)
     988:	8556                	mv	a0,s5
     98a:	00000097          	auipc	ra,0x0
     98e:	d98080e7          	jalr	-616(ra) # 722 <putc>
     992:	8b4a                	mv	s6,s2
      state = 0;
     994:	4981                	li	s3,0
     996:	bd65                	j	84e <vprintf+0x60>
        putc(fd, c);
     998:	85d2                	mv	a1,s4
     99a:	8556                	mv	a0,s5
     99c:	00000097          	auipc	ra,0x0
     9a0:	d86080e7          	jalr	-634(ra) # 722 <putc>
      state = 0;
     9a4:	4981                	li	s3,0
     9a6:	b565                	j	84e <vprintf+0x60>
        s = va_arg(ap, char*);
     9a8:	8b4e                	mv	s6,s3
      state = 0;
     9aa:	4981                	li	s3,0
     9ac:	b54d                	j	84e <vprintf+0x60>
    }
  }
}
     9ae:	70e6                	ld	ra,120(sp)
     9b0:	7446                	ld	s0,112(sp)
     9b2:	74a6                	ld	s1,104(sp)
     9b4:	7906                	ld	s2,96(sp)
     9b6:	69e6                	ld	s3,88(sp)
     9b8:	6a46                	ld	s4,80(sp)
     9ba:	6aa6                	ld	s5,72(sp)
     9bc:	6b06                	ld	s6,64(sp)
     9be:	7be2                	ld	s7,56(sp)
     9c0:	7c42                	ld	s8,48(sp)
     9c2:	7ca2                	ld	s9,40(sp)
     9c4:	7d02                	ld	s10,32(sp)
     9c6:	6de2                	ld	s11,24(sp)
     9c8:	6109                	addi	sp,sp,128
     9ca:	8082                	ret

00000000000009cc <fprintf>:

void
fprintf(int fd, const char *fmt, ...)
{
     9cc:	715d                	addi	sp,sp,-80
     9ce:	ec06                	sd	ra,24(sp)
     9d0:	e822                	sd	s0,16(sp)
     9d2:	1000                	addi	s0,sp,32
     9d4:	e010                	sd	a2,0(s0)
     9d6:	e414                	sd	a3,8(s0)
     9d8:	e818                	sd	a4,16(s0)
     9da:	ec1c                	sd	a5,24(s0)
     9dc:	03043023          	sd	a6,32(s0)
     9e0:	03143423          	sd	a7,40(s0)
  va_list ap;

  va_start(ap, fmt);
     9e4:	fe843423          	sd	s0,-24(s0)
  vprintf(fd, fmt, ap);
     9e8:	8622                	mv	a2,s0
     9ea:	00000097          	auipc	ra,0x0
     9ee:	e04080e7          	jalr	-508(ra) # 7ee <vprintf>
}
     9f2:	60e2                	ld	ra,24(sp)
     9f4:	6442                	ld	s0,16(sp)
     9f6:	6161                	addi	sp,sp,80
     9f8:	8082                	ret

00000000000009fa <printf>:

void
printf(const char *fmt, ...)
{
     9fa:	711d                	addi	sp,sp,-96
     9fc:	ec06                	sd	ra,24(sp)
     9fe:	e822                	sd	s0,16(sp)
     a00:	1000                	addi	s0,sp,32
     a02:	e40c                	sd	a1,8(s0)
     a04:	e810                	sd	a2,16(s0)
     a06:	ec14                	sd	a3,24(s0)
     a08:	f018                	sd	a4,32(s0)
     a0a:	f41c                	sd	a5,40(s0)
     a0c:	03043823          	sd	a6,48(s0)
     a10:	03143c23          	sd	a7,56(s0)
  va_list ap;

  va_start(ap, fmt);
     a14:	00840613          	addi	a2,s0,8
     a18:	fec43423          	sd	a2,-24(s0)
  vprintf(1, fmt, ap);
     a1c:	85aa                	mv	a1,a0
     a1e:	4505                	li	a0,1
     a20:	00000097          	auipc	ra,0x0
     a24:	dce080e7          	jalr	-562(ra) # 7ee <vprintf>
}
     a28:	60e2                	ld	ra,24(sp)
     a2a:	6442                	ld	s0,16(sp)
     a2c:	6125                	addi	sp,sp,96
     a2e:	8082                	ret

0000000000000a30 <free>:
static Header base;
static Header *freep;

void
free(void *ap)
{
     a30:	1141                	addi	sp,sp,-16
     a32:	e422                	sd	s0,8(sp)
     a34:	0800                	addi	s0,sp,16
  Header *bp, *p;

  bp = (Header*)ap - 1;
     a36:	ff050693          	addi	a3,a0,-16
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
     a3a:	00000797          	auipc	a5,0x0
     a3e:	69e7b783          	ld	a5,1694(a5) # 10d8 <freep>
     a42:	a805                	j	a72 <free+0x42>
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break;
  if(bp + bp->s.size == p->s.ptr){
    bp->s.size += p->s.ptr->s.size;
     a44:	4618                	lw	a4,8(a2)
     a46:	9db9                	addw	a1,a1,a4
     a48:	feb52c23          	sw	a1,-8(a0)
    bp->s.ptr = p->s.ptr->s.ptr;
     a4c:	6398                	ld	a4,0(a5)
     a4e:	6318                	ld	a4,0(a4)
     a50:	fee53823          	sd	a4,-16(a0)
     a54:	a091                	j	a98 <free+0x68>
  } else
    bp->s.ptr = p->s.ptr;
  if(p + p->s.size == bp){
    p->s.size += bp->s.size;
     a56:	ff852703          	lw	a4,-8(a0)
     a5a:	9e39                	addw	a2,a2,a4
     a5c:	c790                	sw	a2,8(a5)
    p->s.ptr = bp->s.ptr;
     a5e:	ff053703          	ld	a4,-16(a0)
     a62:	e398                	sd	a4,0(a5)
     a64:	a099                	j	aaa <free+0x7a>
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
     a66:	6398                	ld	a4,0(a5)
     a68:	00e7e463          	bltu	a5,a4,a70 <free+0x40>
     a6c:	00e6ea63          	bltu	a3,a4,a80 <free+0x50>
{
     a70:	87ba                	mv	a5,a4
  for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
     a72:	fed7fae3          	bgeu	a5,a3,a66 <free+0x36>
     a76:	6398                	ld	a4,0(a5)
     a78:	00e6e463          	bltu	a3,a4,a80 <free+0x50>
    if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
     a7c:	fee7eae3          	bltu	a5,a4,a70 <free+0x40>
  if(bp + bp->s.size == p->s.ptr){
     a80:	ff852583          	lw	a1,-8(a0)
     a84:	6390                	ld	a2,0(a5)
     a86:	02059713          	slli	a4,a1,0x20
     a8a:	9301                	srli	a4,a4,0x20
     a8c:	0712                	slli	a4,a4,0x4
     a8e:	9736                	add	a4,a4,a3
     a90:	fae60ae3          	beq	a2,a4,a44 <free+0x14>
    bp->s.ptr = p->s.ptr;
     a94:	fec53823          	sd	a2,-16(a0)
  if(p + p->s.size == bp){
     a98:	4790                	lw	a2,8(a5)
     a9a:	02061713          	slli	a4,a2,0x20
     a9e:	9301                	srli	a4,a4,0x20
     aa0:	0712                	slli	a4,a4,0x4
     aa2:	973e                	add	a4,a4,a5
     aa4:	fae689e3          	beq	a3,a4,a56 <free+0x26>
  } else
    p->s.ptr = bp;
     aa8:	e394                	sd	a3,0(a5)
  freep = p;
     aaa:	00000717          	auipc	a4,0x0
     aae:	62f73723          	sd	a5,1582(a4) # 10d8 <freep>
}
     ab2:	6422                	ld	s0,8(sp)
     ab4:	0141                	addi	sp,sp,16
     ab6:	8082                	ret

0000000000000ab8 <malloc>:
  return freep;
}

void*
malloc(uint nbytes)
{
     ab8:	7139                	addi	sp,sp,-64
     aba:	fc06                	sd	ra,56(sp)
     abc:	f822                	sd	s0,48(sp)
     abe:	f426                	sd	s1,40(sp)
     ac0:	f04a                	sd	s2,32(sp)
     ac2:	ec4e                	sd	s3,24(sp)
     ac4:	e852                	sd	s4,16(sp)
     ac6:	e456                	sd	s5,8(sp)
     ac8:	e05a                	sd	s6,0(sp)
     aca:	0080                	addi	s0,sp,64
  Header *p, *prevp;
  uint nunits;

  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
     acc:	02051493          	slli	s1,a0,0x20
     ad0:	9081                	srli	s1,s1,0x20
     ad2:	04bd                	addi	s1,s1,15
     ad4:	8091                	srli	s1,s1,0x4
     ad6:	0014899b          	addiw	s3,s1,1
     ada:	0485                	addi	s1,s1,1
  if((prevp = freep) == 0){
     adc:	00000517          	auipc	a0,0x0
     ae0:	5fc53503          	ld	a0,1532(a0) # 10d8 <freep>
     ae4:	c515                	beqz	a0,b10 <malloc+0x58>
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
     ae6:	611c                	ld	a5,0(a0)
    if(p->s.size >= nunits){
     ae8:	4798                	lw	a4,8(a5)
     aea:	02977f63          	bgeu	a4,s1,b28 <malloc+0x70>
     aee:	8a4e                	mv	s4,s3
     af0:	0009871b          	sext.w	a4,s3
     af4:	6685                	lui	a3,0x1
     af6:	00d77363          	bgeu	a4,a3,afc <malloc+0x44>
     afa:	6a05                	lui	s4,0x1
     afc:	000a0b1b          	sext.w	s6,s4
  p = sbrk(nu * sizeof(Header));
     b00:	004a1a1b          	slliw	s4,s4,0x4
        p->s.size = nunits;
      }
      freep = prevp;
      return (void*)(p + 1);
    }
    if(p == freep)
     b04:	00000917          	auipc	s2,0x0
     b08:	5d490913          	addi	s2,s2,1492 # 10d8 <freep>
  if(p == (char*)-1)
     b0c:	5afd                	li	s5,-1
     b0e:	a88d                	j	b80 <malloc+0xc8>
    base.s.ptr = freep = prevp = &base;
     b10:	00000797          	auipc	a5,0x0
     b14:	5d878793          	addi	a5,a5,1496 # 10e8 <base>
     b18:	00000717          	auipc	a4,0x0
     b1c:	5cf73023          	sd	a5,1472(a4) # 10d8 <freep>
     b20:	e39c                	sd	a5,0(a5)
    base.s.size = 0;
     b22:	0007a423          	sw	zero,8(a5)
    if(p->s.size >= nunits){
     b26:	b7e1                	j	aee <malloc+0x36>
      if(p->s.size == nunits)
     b28:	02e48b63          	beq	s1,a4,b5e <malloc+0xa6>
        p->s.size -= nunits;
     b2c:	4137073b          	subw	a4,a4,s3
     b30:	c798                	sw	a4,8(a5)
        p += p->s.size;
     b32:	1702                	slli	a4,a4,0x20
     b34:	9301                	srli	a4,a4,0x20
     b36:	0712                	slli	a4,a4,0x4
     b38:	97ba                	add	a5,a5,a4
        p->s.size = nunits;
     b3a:	0137a423          	sw	s3,8(a5)
      freep = prevp;
     b3e:	00000717          	auipc	a4,0x0
     b42:	58a73d23          	sd	a0,1434(a4) # 10d8 <freep>
      return (void*)(p + 1);
     b46:	01078513          	addi	a0,a5,16
      if((p = morecore(nunits)) == 0)
        return 0;
  }
}
     b4a:	70e2                	ld	ra,56(sp)
     b4c:	7442                	ld	s0,48(sp)
     b4e:	74a2                	ld	s1,40(sp)
     b50:	7902                	ld	s2,32(sp)
     b52:	69e2                	ld	s3,24(sp)
     b54:	6a42                	ld	s4,16(sp)
     b56:	6aa2                	ld	s5,8(sp)
     b58:	6b02                	ld	s6,0(sp)
     b5a:	6121                	addi	sp,sp,64
     b5c:	8082                	ret
        prevp->s.ptr = p->s.ptr;
     b5e:	6398                	ld	a4,0(a5)
     b60:	e118                	sd	a4,0(a0)
     b62:	bff1                	j	b3e <malloc+0x86>
  hp->s.size = nu;
     b64:	01652423          	sw	s6,8(a0)
  free((void*)(hp + 1));
     b68:	0541                	addi	a0,a0,16
     b6a:	00000097          	auipc	ra,0x0
     b6e:	ec6080e7          	jalr	-314(ra) # a30 <free>
  return freep;
     b72:	00093503          	ld	a0,0(s2)
      if((p = morecore(nunits)) == 0)
     b76:	d971                	beqz	a0,b4a <malloc+0x92>
  for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
     b78:	611c                	ld	a5,0(a0)
    if(p->s.size >= nunits){
     b7a:	4798                	lw	a4,8(a5)
     b7c:	fa9776e3          	bgeu	a4,s1,b28 <malloc+0x70>
    if(p == freep)
     b80:	00093703          	ld	a4,0(s2)
     b84:	853e                	mv	a0,a5
     b86:	fef719e3          	bne	a4,a5,b78 <malloc+0xc0>
  p = sbrk(nu * sizeof(Header));
     b8a:	8552                	mv	a0,s4
     b8c:	00000097          	auipc	ra,0x0
     b90:	b7e080e7          	jalr	-1154(ra) # 70a <sbrk>
  if(p == (char*)-1)
     b94:	fd5518e3          	bne	a0,s5,b64 <malloc+0xac>
        return 0;
     b98:	4501                	li	a0,0
     b9a:	bf45                	j	b4a <malloc+0x92>

0000000000000b9c <setjmp>:
     b9c:	e100                	sd	s0,0(a0)
     b9e:	e504                	sd	s1,8(a0)
     ba0:	01253823          	sd	s2,16(a0)
     ba4:	01353c23          	sd	s3,24(a0)
     ba8:	03453023          	sd	s4,32(a0)
     bac:	03553423          	sd	s5,40(a0)
     bb0:	03653823          	sd	s6,48(a0)
     bb4:	03753c23          	sd	s7,56(a0)
     bb8:	05853023          	sd	s8,64(a0)
     bbc:	05953423          	sd	s9,72(a0)
     bc0:	05a53823          	sd	s10,80(a0)
     bc4:	05b53c23          	sd	s11,88(a0)
     bc8:	06153023          	sd	ra,96(a0)
     bcc:	06253423          	sd	sp,104(a0)
     bd0:	4501                	li	a0,0
     bd2:	8082                	ret

0000000000000bd4 <longjmp>:
     bd4:	6100                	ld	s0,0(a0)
     bd6:	6504                	ld	s1,8(a0)
     bd8:	01053903          	ld	s2,16(a0)
     bdc:	01853983          	ld	s3,24(a0)
     be0:	02053a03          	ld	s4,32(a0)
     be4:	02853a83          	ld	s5,40(a0)
     be8:	03053b03          	ld	s6,48(a0)
     bec:	03853b83          	ld	s7,56(a0)
     bf0:	04053c03          	ld	s8,64(a0)
     bf4:	04853c83          	ld	s9,72(a0)
     bf8:	05053d03          	ld	s10,80(a0)
     bfc:	05853d83          	ld	s11,88(a0)
     c00:	06053083          	ld	ra,96(a0)
     c04:	06853103          	ld	sp,104(a0)
     c08:	c199                	beqz	a1,c0e <longjmp_1>
     c0a:	852e                	mv	a0,a1
     c0c:	8082                	ret

0000000000000c0e <longjmp_1>:
     c0e:	4505                	li	a0,1
     c10:	8082                	ret

0000000000000c12 <thread_create>:
static struct thread* current_thread = NULL;
static int id = 1;
static jmp_buf env_st;
static jmp_buf env_tmp;

struct thread *thread_create(void (*f)(void *), void *arg){
     c12:	7139                	addi	sp,sp,-64
     c14:	fc06                	sd	ra,56(sp)
     c16:	f822                	sd	s0,48(sp)
     c18:	f426                	sd	s1,40(sp)
     c1a:	f04a                	sd	s2,32(sp)
     c1c:	ec4e                	sd	s3,24(sp)
     c1e:	e852                	sd	s4,16(sp)
     c20:	e456                	sd	s5,8(sp)
     c22:	0080                	addi	s0,sp,64
     c24:	8a2a                	mv	s4,a0
     c26:	89ae                	mv	s3,a1
    struct thread *t = (struct thread*) malloc(sizeof(struct thread));
     c28:	14800513          	li	a0,328
     c2c:	00000097          	auipc	ra,0x0
     c30:	e8c080e7          	jalr	-372(ra) # ab8 <malloc>
     c34:	84aa                	mv	s1,a0
    unsigned long new_stack_p1;
    unsigned long new_stack1;
    new_stack1 = (unsigned long) malloc(sizeof(unsigned long) * 0x100);
     c36:	6a85                	lui	s5,0x1
     c38:	800a8513          	addi	a0,s5,-2048 # 800 <vprintf+0x12>
     c3c:	00000097          	auipc	ra,0x0
     c40:	e7c080e7          	jalr	-388(ra) # ab8 <malloc>
     c44:	892a                	mv	s2,a0
    new_stack_p1 = new_stack1 + 0x100 * 8 - 0x2 * 8;
    unsigned long new_stack_p2;
    unsigned long new_stack2;
    new_stack2 = (unsigned long) malloc(sizeof(unsigned long) * 0x100);
     c46:	800a8513          	addi	a0,s5,-2048
     c4a:	00000097          	auipc	ra,0x0
     c4e:	e6e080e7          	jalr	-402(ra) # ab8 <malloc>
    new_stack_p2 = new_stack2 + 0x100 * 8 - 0x2 * 8;
    t->fp = f;
     c52:	0144b023          	sd	s4,0(s1)
    t->arg = arg;
     c56:	0134b423          	sd	s3,8(s1)
    t->ID = id;
     c5a:	00000697          	auipc	a3,0x0
     c5e:	47a68693          	addi	a3,a3,1146 # 10d4 <id>
     c62:	4298                	lw	a4,0(a3)
     c64:	0ae4a223          	sw	a4,164(s1)
    t->buf_set = 0;
     c68:	0a04a023          	sw	zero,160(s1)
    t->stack1 = (void*) new_stack1;
     c6c:	0124b823          	sd	s2,16(s1)
    new_stack_p1 = new_stack1 + 0x100 * 8 - 0x2 * 8;
     c70:	7f090913          	addi	s2,s2,2032
    t->stack_p1 = (void*) new_stack_p1;
     c74:	0124bc23          	sd	s2,24(s1)
    t->stack2 = (void*) new_stack2;
     c78:	f088                	sd	a0,32(s1)
    new_stack_p2 = new_stack2 + 0x100 * 8 - 0x2 * 8;
     c7a:	7f050793          	addi	a5,a0,2032
    t->stack_p2 = (void*) new_stack_p2;
     c7e:	f49c                	sd	a5,40(s1)
    id++;
     c80:	2705                	addiw	a4,a4,1
     c82:	c298                	sw	a4,0(a3)

    // part 2
    t->sig_handler[0] = NULL_FUNC;
     c84:	57fd                	li	a5,-1
     c86:	fcdc                	sd	a5,184(s1)
    t->sig_handler[1] = NULL_FUNC;
     c88:	e0fc                	sd	a5,192(s1)
    t->signo = -1;
     c8a:	0cf4a423          	sw	a5,200(s1)
    t->handler_buf_set = 0;
     c8e:	1404a023          	sw	zero,320(s1)
    return t;
}
     c92:	8526                	mv	a0,s1
     c94:	70e2                	ld	ra,56(sp)
     c96:	7442                	ld	s0,48(sp)
     c98:	74a2                	ld	s1,40(sp)
     c9a:	7902                	ld	s2,32(sp)
     c9c:	69e2                	ld	s3,24(sp)
     c9e:	6a42                	ld	s4,16(sp)
     ca0:	6aa2                	ld	s5,8(sp)
     ca2:	6121                	addi	sp,sp,64
     ca4:	8082                	ret

0000000000000ca6 <thread_add_runqueue>:

void thread_add_runqueue(struct thread *t){
     ca6:	1141                	addi	sp,sp,-16
     ca8:	e422                	sd	s0,8(sp)
     caa:	0800                	addi	s0,sp,16
    if (current_thread == NULL){
     cac:	00000797          	auipc	a5,0x0
     cb0:	4347b783          	ld	a5,1076(a5) # 10e0 <current_thread>
     cb4:	cf91                	beqz	a5,cd0 <thread_add_runqueue+0x2a>
        t->previous = t;
        t->next = t;
    }
    else{
        // TODO
        current_thread->previous->next = t;
     cb6:	77d8                	ld	a4,168(a5)
     cb8:	fb48                	sd	a0,176(a4)
        t->previous = current_thread->previous;
     cba:	77d8                	ld	a4,168(a5)
     cbc:	f558                	sd	a4,168(a0)
        current_thread->previous = t;
     cbe:	f7c8                	sd	a0,168(a5)
        t->next = current_thread;
     cc0:	f95c                	sd	a5,176(a0)

        t->sig_handler[0] = current_thread->sig_handler[0];
     cc2:	7fd8                	ld	a4,184(a5)
     cc4:	fd58                	sd	a4,184(a0)
        t->sig_handler[1] = current_thread->sig_handler[1];
     cc6:	63fc                	ld	a5,192(a5)
     cc8:	e17c                	sd	a5,192(a0)
    }
}
     cca:	6422                	ld	s0,8(sp)
     ccc:	0141                	addi	sp,sp,16
     cce:	8082                	ret
        current_thread = t;
     cd0:	00000797          	auipc	a5,0x0
     cd4:	40a7b823          	sd	a0,1040(a5) # 10e0 <current_thread>
        t->previous = t;
     cd8:	f548                	sd	a0,168(a0)
        t->next = t;
     cda:	f948                	sd	a0,176(a0)
     cdc:	b7fd                	j	cca <thread_add_runqueue+0x24>

0000000000000cde <schedule>:
                longjmp(current_thread->handler_env, 1);
        }
    }
}

void schedule(void){
     cde:	1141                	addi	sp,sp,-16
     ce0:	e422                	sd	s0,8(sp)
     ce2:	0800                	addi	s0,sp,16
    // TODO
    current_thread = current_thread->next;
     ce4:	00000797          	auipc	a5,0x0
     ce8:	3fc78793          	addi	a5,a5,1020 # 10e0 <current_thread>
     cec:	6398                	ld	a4,0(a5)
     cee:	7b58                	ld	a4,176(a4)
     cf0:	e398                	sd	a4,0(a5)
}
     cf2:	6422                	ld	s0,8(sp)
     cf4:	0141                	addi	sp,sp,16
     cf6:	8082                	ret

0000000000000cf8 <thread_exit>:

void thread_exit(void){
     cf8:	1101                	addi	sp,sp,-32
     cfa:	ec06                	sd	ra,24(sp)
     cfc:	e822                	sd	s0,16(sp)
     cfe:	e426                	sd	s1,8(sp)
     d00:	e04a                	sd	s2,0(sp)
     d02:	1000                	addi	s0,sp,32
    if(current_thread->next != current_thread){
     d04:	00000797          	auipc	a5,0x0
     d08:	3dc7b783          	ld	a5,988(a5) # 10e0 <current_thread>
     d0c:	7bd8                	ld	a4,176(a5)
     d0e:	04e78863          	beq	a5,a4,d5e <thread_exit+0x66>
        // TODO
        current_thread->previous->next = current_thread->next;
     d12:	77d4                	ld	a3,168(a5)
     d14:	fad8                	sd	a4,176(a3)
        current_thread->next->previous = current_thread->previous;
     d16:	77d4                	ld	a3,168(a5)
     d18:	f754                	sd	a3,168(a4)
        struct thread *next = current_thread->next;
     d1a:	0b07b903          	ld	s2,176(a5)
        free(current_thread->stack1);
     d1e:	6b88                	ld	a0,16(a5)
     d20:	00000097          	auipc	ra,0x0
     d24:	d10080e7          	jalr	-752(ra) # a30 <free>
        free(current_thread->stack2);
     d28:	00000497          	auipc	s1,0x0
     d2c:	3b848493          	addi	s1,s1,952 # 10e0 <current_thread>
     d30:	609c                	ld	a5,0(s1)
     d32:	7388                	ld	a0,32(a5)
     d34:	00000097          	auipc	ra,0x0
     d38:	cfc080e7          	jalr	-772(ra) # a30 <free>
        free(current_thread);
     d3c:	6088                	ld	a0,0(s1)
     d3e:	00000097          	auipc	ra,0x0
     d42:	cf2080e7          	jalr	-782(ra) # a30 <free>
        current_thread = next;
     d46:	0124b023          	sd	s2,0(s1)
        dispatch();
     d4a:	00000097          	auipc	ra,0x0
     d4e:	054080e7          	jalr	84(ra) # d9e <dispatch>
        free(current_thread->stack2);
        free(current_thread);
        current_thread = NULL;
        longjmp(env_st, 1);
    }
}
     d52:	60e2                	ld	ra,24(sp)
     d54:	6442                	ld	s0,16(sp)
     d56:	64a2                	ld	s1,8(sp)
     d58:	6902                	ld	s2,0(sp)
     d5a:	6105                	addi	sp,sp,32
     d5c:	8082                	ret
        free(current_thread->stack1);
     d5e:	6b88                	ld	a0,16(a5)
     d60:	00000097          	auipc	ra,0x0
     d64:	cd0080e7          	jalr	-816(ra) # a30 <free>
        free(current_thread->stack2);
     d68:	00000497          	auipc	s1,0x0
     d6c:	37848493          	addi	s1,s1,888 # 10e0 <current_thread>
     d70:	609c                	ld	a5,0(s1)
     d72:	7388                	ld	a0,32(a5)
     d74:	00000097          	auipc	ra,0x0
     d78:	cbc080e7          	jalr	-836(ra) # a30 <free>
        free(current_thread);
     d7c:	6088                	ld	a0,0(s1)
     d7e:	00000097          	auipc	ra,0x0
     d82:	cb2080e7          	jalr	-846(ra) # a30 <free>
        current_thread = NULL;
     d86:	0004b023          	sd	zero,0(s1)
        longjmp(env_st, 1);
     d8a:	4585                	li	a1,1
     d8c:	00000517          	auipc	a0,0x0
     d90:	36c50513          	addi	a0,a0,876 # 10f8 <env_st>
     d94:	00000097          	auipc	ra,0x0
     d98:	e40080e7          	jalr	-448(ra) # bd4 <longjmp>
}
     d9c:	bf5d                	j	d52 <thread_exit+0x5a>

0000000000000d9e <dispatch>:
void dispatch(void){
     d9e:	1101                	addi	sp,sp,-32
     da0:	ec06                	sd	ra,24(sp)
     da2:	e822                	sd	s0,16(sp)
     da4:	e426                	sd	s1,8(sp)
     da6:	1000                	addi	s0,sp,32
    if (current_thread->signo == -1){
     da8:	00000517          	auipc	a0,0x0
     dac:	33853503          	ld	a0,824(a0) # 10e0 <current_thread>
     db0:	0c852783          	lw	a5,200(a0)
     db4:	577d                	li	a4,-1
     db6:	06e78f63          	beq	a5,a4,e34 <dispatch+0x96>
        if (current_thread->sig_handler[current_thread->signo] == NULL_FUNC)
     dba:	07d9                	addi	a5,a5,22
     dbc:	078e                	slli	a5,a5,0x3
     dbe:	97aa                	add	a5,a5,a0
     dc0:	6798                	ld	a4,8(a5)
     dc2:	57fd                	li	a5,-1
     dc4:	0cf70b63          	beq	a4,a5,e9a <dispatch+0xfc>
            if (current_thread->handler_buf_set == 0){
     dc8:	14052783          	lw	a5,320(a0)
     dcc:	12079a63          	bnez	a5,f00 <dispatch+0x162>
                if (setjmp(env_tmp) == 0){
     dd0:	00000517          	auipc	a0,0x0
     dd4:	39850513          	addi	a0,a0,920 # 1168 <env_tmp>
     dd8:	00000097          	auipc	ra,0x0
     ddc:	dc4080e7          	jalr	-572(ra) # b9c <setjmp>
     de0:	c171                	beqz	a0,ea4 <dispatch+0x106>
                    current_thread->sig_handler[current_thread->signo](current_thread->signo);
     de2:	00000497          	auipc	s1,0x0
     de6:	2fe48493          	addi	s1,s1,766 # 10e0 <current_thread>
     dea:	609c                	ld	a5,0(s1)
     dec:	0c87a503          	lw	a0,200(a5)
     df0:	01650713          	addi	a4,a0,22
     df4:	070e                	slli	a4,a4,0x3
     df6:	97ba                	add	a5,a5,a4
     df8:	679c                	ld	a5,8(a5)
     dfa:	9782                	jalr	a5
                    current_thread->signo = -1;
     dfc:	6088                	ld	a0,0(s1)
     dfe:	57fd                	li	a5,-1
     e00:	0cf52423          	sw	a5,200(a0)
                    if (current_thread->buf_set == 0){
     e04:	0a052783          	lw	a5,160(a0)
     e08:	e7e5                	bnez	a5,ef0 <dispatch+0x152>
                        if (setjmp(env_tmp) == 0){
     e0a:	00000517          	auipc	a0,0x0
     e0e:	35e50513          	addi	a0,a0,862 # 1168 <env_tmp>
     e12:	00000097          	auipc	ra,0x0
     e16:	d8a080e7          	jalr	-630(ra) # b9c <setjmp>
     e1a:	c945                	beqz	a0,eca <dispatch+0x12c>
                            current_thread->fp(current_thread->arg);
     e1c:	00000797          	auipc	a5,0x0
     e20:	2c47b783          	ld	a5,708(a5) # 10e0 <current_thread>
     e24:	6398                	ld	a4,0(a5)
     e26:	6788                	ld	a0,8(a5)
     e28:	9702                	jalr	a4
                            thread_exit();
     e2a:	00000097          	auipc	ra,0x0
     e2e:	ece080e7          	jalr	-306(ra) # cf8 <thread_exit>
     e32:	a8f1                	j	f0e <dispatch+0x170>
        if (current_thread->buf_set == 0){
     e34:	0a052783          	lw	a5,160(a0)
     e38:	eba9                	bnez	a5,e8a <dispatch+0xec>
            if (setjmp(env_tmp) == 0){
     e3a:	00000517          	auipc	a0,0x0
     e3e:	32e50513          	addi	a0,a0,814 # 1168 <env_tmp>
     e42:	00000097          	auipc	ra,0x0
     e46:	d5a080e7          	jalr	-678(ra) # b9c <setjmp>
     e4a:	cd09                	beqz	a0,e64 <dispatch+0xc6>
                current_thread->fp(current_thread->arg);
     e4c:	00000797          	auipc	a5,0x0
     e50:	2947b783          	ld	a5,660(a5) # 10e0 <current_thread>
     e54:	6398                	ld	a4,0(a5)
     e56:	6788                	ld	a0,8(a5)
     e58:	9702                	jalr	a4
                thread_exit();
     e5a:	00000097          	auipc	ra,0x0
     e5e:	e9e080e7          	jalr	-354(ra) # cf8 <thread_exit>
     e62:	a075                	j	f0e <dispatch+0x170>
                env_tmp->sp = (unsigned long) current_thread->stack_p1;
     e64:	00000797          	auipc	a5,0x0
     e68:	27c7b783          	ld	a5,636(a5) # 10e0 <current_thread>
     e6c:	6f9c                	ld	a5,24(a5)
     e6e:	00000717          	auipc	a4,0x0
     e72:	36f73123          	sd	a5,866(a4) # 11d0 <env_tmp+0x68>
                longjmp(env_tmp, 1);
     e76:	4585                	li	a1,1
     e78:	00000517          	auipc	a0,0x0
     e7c:	2f050513          	addi	a0,a0,752 # 1168 <env_tmp>
     e80:	00000097          	auipc	ra,0x0
     e84:	d54080e7          	jalr	-684(ra) # bd4 <longjmp>
     e88:	a059                	j	f0e <dispatch+0x170>
            longjmp(current_thread->env, 1);
     e8a:	4585                	li	a1,1
     e8c:	03050513          	addi	a0,a0,48
     e90:	00000097          	auipc	ra,0x0
     e94:	d44080e7          	jalr	-700(ra) # bd4 <longjmp>
     e98:	a89d                	j	f0e <dispatch+0x170>
            thread_exit();
     e9a:	00000097          	auipc	ra,0x0
     e9e:	e5e080e7          	jalr	-418(ra) # cf8 <thread_exit>
     ea2:	a0b5                	j	f0e <dispatch+0x170>
                    env_tmp->sp = (unsigned long) current_thread->stack_p2;
     ea4:	00000797          	auipc	a5,0x0
     ea8:	23c7b783          	ld	a5,572(a5) # 10e0 <current_thread>
     eac:	779c                	ld	a5,40(a5)
     eae:	00000717          	auipc	a4,0x0
     eb2:	32f73123          	sd	a5,802(a4) # 11d0 <env_tmp+0x68>
                    longjmp(env_tmp, 1);
     eb6:	4585                	li	a1,1
     eb8:	00000517          	auipc	a0,0x0
     ebc:	2b050513          	addi	a0,a0,688 # 1168 <env_tmp>
     ec0:	00000097          	auipc	ra,0x0
     ec4:	d14080e7          	jalr	-748(ra) # bd4 <longjmp>
     ec8:	a099                	j	f0e <dispatch+0x170>
                            env_tmp->sp = (unsigned long) current_thread->stack_p1;
     eca:	00000797          	auipc	a5,0x0
     ece:	2167b783          	ld	a5,534(a5) # 10e0 <current_thread>
     ed2:	6f9c                	ld	a5,24(a5)
     ed4:	00000717          	auipc	a4,0x0
     ed8:	2ef73e23          	sd	a5,764(a4) # 11d0 <env_tmp+0x68>
                            longjmp(env_tmp, 1);
     edc:	4585                	li	a1,1
     ede:	00000517          	auipc	a0,0x0
     ee2:	28a50513          	addi	a0,a0,650 # 1168 <env_tmp>
     ee6:	00000097          	auipc	ra,0x0
     eea:	cee080e7          	jalr	-786(ra) # bd4 <longjmp>
     eee:	a005                	j	f0e <dispatch+0x170>
                        longjmp(current_thread->env, 1);
     ef0:	4585                	li	a1,1
     ef2:	03050513          	addi	a0,a0,48
     ef6:	00000097          	auipc	ra,0x0
     efa:	cde080e7          	jalr	-802(ra) # bd4 <longjmp>
     efe:	a801                	j	f0e <dispatch+0x170>
                longjmp(current_thread->handler_env, 1);
     f00:	4585                	li	a1,1
     f02:	0d050513          	addi	a0,a0,208
     f06:	00000097          	auipc	ra,0x0
     f0a:	cce080e7          	jalr	-818(ra) # bd4 <longjmp>
}
     f0e:	60e2                	ld	ra,24(sp)
     f10:	6442                	ld	s0,16(sp)
     f12:	64a2                	ld	s1,8(sp)
     f14:	6105                	addi	sp,sp,32
     f16:	8082                	ret

0000000000000f18 <thread_yield>:
void thread_yield(void){
     f18:	1141                	addi	sp,sp,-16
     f1a:	e406                	sd	ra,8(sp)
     f1c:	e022                	sd	s0,0(sp)
     f1e:	0800                	addi	s0,sp,16
    if (current_thread->signo == -1 && setjmp(current_thread->env) == 0){
     f20:	00000517          	auipc	a0,0x0
     f24:	1c053503          	ld	a0,448(a0) # 10e0 <current_thread>
     f28:	0c852703          	lw	a4,200(a0)
     f2c:	57fd                	li	a5,-1
     f2e:	00f70d63          	beq	a4,a5,f48 <thread_yield+0x30>
    if (current_thread->signo != -1 && setjmp(current_thread->handler_env) == 0){
     f32:	0d050513          	addi	a0,a0,208
     f36:	00000097          	auipc	ra,0x0
     f3a:	c66080e7          	jalr	-922(ra) # b9c <setjmp>
     f3e:	c531                	beqz	a0,f8a <thread_yield+0x72>
}
     f40:	60a2                	ld	ra,8(sp)
     f42:	6402                	ld	s0,0(sp)
     f44:	0141                	addi	sp,sp,16
     f46:	8082                	ret
    if (current_thread->signo == -1 && setjmp(current_thread->env) == 0){
     f48:	03050513          	addi	a0,a0,48
     f4c:	00000097          	auipc	ra,0x0
     f50:	c50080e7          	jalr	-944(ra) # b9c <setjmp>
     f54:	c919                	beqz	a0,f6a <thread_yield+0x52>
    if (current_thread->signo != -1 && setjmp(current_thread->handler_env) == 0){
     f56:	00000517          	auipc	a0,0x0
     f5a:	18a53503          	ld	a0,394(a0) # 10e0 <current_thread>
     f5e:	0c852703          	lw	a4,200(a0)
     f62:	57fd                	li	a5,-1
     f64:	fcf70ee3          	beq	a4,a5,f40 <thread_yield+0x28>
     f68:	b7e9                	j	f32 <thread_yield+0x1a>
        current_thread->buf_set = 1;
     f6a:	00000797          	auipc	a5,0x0
     f6e:	1767b783          	ld	a5,374(a5) # 10e0 <current_thread>
     f72:	4705                	li	a4,1
     f74:	0ae7a023          	sw	a4,160(a5)
        schedule();
     f78:	00000097          	auipc	ra,0x0
     f7c:	d66080e7          	jalr	-666(ra) # cde <schedule>
        dispatch();
     f80:	00000097          	auipc	ra,0x0
     f84:	e1e080e7          	jalr	-482(ra) # d9e <dispatch>
     f88:	b7f9                	j	f56 <thread_yield+0x3e>
        current_thread->handler_buf_set = 1;
     f8a:	00000797          	auipc	a5,0x0
     f8e:	1567b783          	ld	a5,342(a5) # 10e0 <current_thread>
     f92:	4705                	li	a4,1
     f94:	14e7a023          	sw	a4,320(a5)
        schedule();
     f98:	00000097          	auipc	ra,0x0
     f9c:	d46080e7          	jalr	-698(ra) # cde <schedule>
        dispatch();
     fa0:	00000097          	auipc	ra,0x0
     fa4:	dfe080e7          	jalr	-514(ra) # d9e <dispatch>
}
     fa8:	bf61                	j	f40 <thread_yield+0x28>

0000000000000faa <thread_start_threading>:

void thread_start_threading(void){
     faa:	1141                	addi	sp,sp,-16
     fac:	e406                	sd	ra,8(sp)
     fae:	e022                	sd	s0,0(sp)
     fb0:	0800                	addi	s0,sp,16
    // TODO
    if (setjmp(env_st) == 0)
     fb2:	00000517          	auipc	a0,0x0
     fb6:	14650513          	addi	a0,a0,326 # 10f8 <env_st>
     fba:	00000097          	auipc	ra,0x0
     fbe:	be2080e7          	jalr	-1054(ra) # b9c <setjmp>
     fc2:	c509                	beqz	a0,fcc <thread_start_threading+0x22>
        dispatch();
}
     fc4:	60a2                	ld	ra,8(sp)
     fc6:	6402                	ld	s0,0(sp)
     fc8:	0141                	addi	sp,sp,16
     fca:	8082                	ret
        dispatch();
     fcc:	00000097          	auipc	ra,0x0
     fd0:	dd2080e7          	jalr	-558(ra) # d9e <dispatch>
}
     fd4:	bfc5                	j	fc4 <thread_start_threading+0x1a>

0000000000000fd6 <thread_register_handler>:

// part 2
void thread_register_handler(int signo, void (*handler)(int)){
     fd6:	1141                	addi	sp,sp,-16
     fd8:	e422                	sd	s0,8(sp)
     fda:	0800                	addi	s0,sp,16
    // TODO
    current_thread->sig_handler[signo] = handler;
     fdc:	0559                	addi	a0,a0,22
     fde:	050e                	slli	a0,a0,0x3
     fe0:	00000797          	auipc	a5,0x0
     fe4:	1007b783          	ld	a5,256(a5) # 10e0 <current_thread>
     fe8:	953e                	add	a0,a0,a5
     fea:	e50c                	sd	a1,8(a0)
}
     fec:	6422                	ld	s0,8(sp)
     fee:	0141                	addi	sp,sp,16
     ff0:	8082                	ret

0000000000000ff2 <thread_kill>:

void thread_kill(struct thread *t, int signo){
     ff2:	1141                	addi	sp,sp,-16
     ff4:	e422                	sd	s0,8(sp)
     ff6:	0800                	addi	s0,sp,16
    // TODO
    t->signo = signo;
     ff8:	0cb52423          	sw	a1,200(a0)
     ffc:	6422                	ld	s0,8(sp)
     ffe:	0141                	addi	sp,sp,16
    1000:	8082                	ret
