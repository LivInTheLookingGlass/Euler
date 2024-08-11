/*
Project Euler Problem 13

Problem:

Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
37107287533902102798797998220837590246510135740250
46376937677490009712648124896970078050417018260538
74324986199524741059474233309513058123726617309629
91942213363574161572522430563301811072406154908250
23067588207539346171171980310421047513778063246676
89261670696623633820136378418383684178734361726757
28112879812849979408065481931592621691275889832738
44274228917432520321923589422876796487670272189318
47451445736001306439091167216856844588711603153276
70386486105843025439939619828917593665686757934951
62176457141856560629502157223196586755079324193331
64906352462741904929101432445813822663347944758178
92575867718337217661963751590579239728245598838407
58203565325359399008402633568948830189458628227828
80181199384826282014278194139940567587151170094390
35398664372827112653829987240784473053190104293586
86515506006295864861532075273371959191420517255829
71693888707715466499115593487603532921714970056938
54370070576826684624621495650076471787294438377604
53282654108756828443191190634694037855217779295145
36123272525000296071075082563815656710885258350721
45876576172410976447339110607218265236877223636045
17423706905851860660448207621209813287860733969412
81142660418086830619328460811191061556940512689692
51934325451728388641918047049293215058642563049483
62467221648435076201727918039944693004732956340691
15732444386908125794514089057706229429197107928209
55037687525678773091862540744969844508330393682126
18336384825330154686196124348767681297534375946515
80386287592878490201521685554828717201219257766954
78182833757993103614740356856449095527097864797581
16726320100436897842553539920931837441497806860984
48403098129077791799088218795327364475675590848030
87086987551392711854517078544161852424320693150332
59959406895756536782107074926966537676326235447210
69793950679652694742597709739166693763042633987085
41052684708299085211399427365734116182760315001271
65378607361501080857009149939512557028198746004375
35829035317434717326932123578154982629742552737307
94953759765105305946966067683156574377167401875275
88902802571733229619176668713819931811048770190271
25267680276078003013678680992525463401061632866526
36270218540497705585629946580636237993140746255962
24074486908231174977792365466257246923322810917141
91430288197103288597806669760892938638285025333403
34413065578016127815921815005561868836468420090470
23053081172816430487623791969842487255036638784583
11487696932154902810424020138335124462181441773470
63783299490636259666498587618221225225512486764533
67720186971698544312419572409913959008952310058822
95548255300263520781532296796249481641953868218774
76085327132285723110424803456124867697064507995236
37774242535411291684276865538926205024910326572967
23701913275725675285653248258265463092207058596522
29798860272258331913126375147341994889534765745501
18495701454879288984856827726077713721403798879715
38298203783031473527721580348144513491373226651381
34829543829199918180278916522431027392251122869539
40957953066405232632538044100059654939159879593635
29746152185502371307642255121183693803580388584903
41698116222072977186158236678424689157993532961922
62467957194401269043877107275048102390895523597457
23189706772547915061505504953922979530901129967519
86188088225875314529584099251203829009407770775672
11306739708304724483816533873502340845647058077308
82959174767140363198008187129011875491310547126581
97623331044818386269515456334926366572897563400500
42846280183517070527831839425882145521227251250327
55121603546981200581762165212827652751691296897789
32238195734329339946437501907836945765883352399886
75506164965184775180738168837861091527357929701337
62177842752192623401942399639168044983993173312731
32924185707147349566916674687634660915035914677504
99518671430235219628894890102423325116913619626622
73267460800591547471830798392868535206946944540724
76841822524674417161514036427982273348055556214818
97142617910342598647204516893989422179826088076852
87783646182799346313767754307809363333018982642090
10848802521674670883215120185883543223812876952786
71329612474782464538636993009049310363619763878039
62184073572399794223406235393808339651327408011116
66627891981488087797941876876144230030984490851411
60661826293682836764744779239180335110989069790714
85786944089552990653640447425576083659976645795096
66024396409905389607120198219976047599490197230297
64913982680032973156037120041377903785566085089252
16730939319872750275468906903707539413042652315011
94809377245048795150954100921645863754710598436791
78639167021187492431995700641917969777599028300699
15368713711936614952811305876380278410754449733078
40789923115535562561142322423255033685442488917353
44889911501440648020369068063960672322193204149535
41503128880339536053299340368006977710650566631954
81234880673210146739058568557934581403627822703280
82616570773948327592232845941706525094512325230608
22918802058777319719839450180888072429661980811197
77158542502016545090413245809786882778948721859617
72107838435069186155435662884062257473692284509516
20849603980134001723930671666823555245252804609722
53503534226472524250874054075591789781264330331690
*/
package euler;

public class p0013 implements IEuler {
    @Override
    public Object answer() {
        long[][] numbers = new long[][] { new long[] { 37107287533902L, 102798797998220837L, 590246510135740250L },
                new long[] { 46376937677490L, 9712648124896970L, 78050417018260538L },
                new long[] { 74324986199524L, 741059474233309513L, 58123726617309629L },
                new long[] { 91942213363574L, 161572522430563301L, 811072406154908250L },
                new long[] { 23067588207539L, 346171171980310421L, 47513778063246676L },
                new long[] { 89261670696623L, 633820136378418383L, 684178734361726757L },
                new long[] { 28112879812849L, 979408065481931592L, 621691275889832738L },
                new long[] { 44274228917432L, 520321923589422876L, 796487670272189318L },
                new long[] { 47451445736001L, 306439091167216856L, 844588711603153276L },
                new long[] { 70386486105843L, 25439939619828917L, 593665686757934951L },
                new long[] { 62176457141856L, 560629502157223196L, 586755079324193331L },
                new long[] { 64906352462741L, 904929101432445813L, 822663347944758178L },
                new long[] { 92575867718337L, 217661963751590579L, 239728245598838407L },
                new long[] { 58203565325359L, 399008402633568948L, 830189458628227828L },
                new long[] { 80181199384826L, 282014278194139940L, 567587151170094390L },
                new long[] { 35398664372827L, 112653829987240784L, 473053190104293586L },
                new long[] { 86515506006295L, 864861532075273371L, 959191420517255829L },
                new long[] { 71693888707715L, 466499115593487603L, 532921714970056938L },
                new long[] { 54370070576826L, 684624621495650076L, 471787294438377604L },
                new long[] { 53282654108756L, 828443191190634694L, 37855217779295145L },
                new long[] { 36123272525000L, 296071075082563815L, 656710885258350721L },
                new long[] { 45876576172410L, 976447339110607218L, 265236877223636045L },
                new long[] { 17423706905851L, 860660448207621209L, 813287860733969412L },
                new long[] { 81142660418086L, 830619328460811191L, 61556940512689692L },
                new long[] { 51934325451728L, 388641918047049293L, 215058642563049483L },
                new long[] { 62467221648435L, 76201727918039944L, 693004732956340691L },
                new long[] { 15732444386908L, 125794514089057706L, 229429197107928209L },
                new long[] { 55037687525678L, 773091862540744969L, 844508330393682126L },
                new long[] { 18336384825330L, 154686196124348767L, 681297534375946515L },
                new long[] { 80386287592878L, 490201521685554828L, 717201219257766954L },
                new long[] { 78182833757993L, 103614740356856449L, 95527097864797581L },
                new long[] { 16726320100436L, 897842553539920931L, 837441497806860984L },
                new long[] { 48403098129077L, 791799088218795327L, 364475675590848030L },
                new long[] { 87086987551392L, 711854517078544161L, 852424320693150332L },
                new long[] { 59959406895756L, 536782107074926966L, 537676326235447210L },
                new long[] { 69793950679652L, 694742597709739166L, 693763042633987085L },
                new long[] { 41052684708299L, 85211399427365734L, 116182760315001271L },
                new long[] { 65378607361501L, 80857009149939512L, 557028198746004375L },
                new long[] { 35829035317434L, 717326932123578154L, 982629742552737307L },
                new long[] { 94953759765105L, 305946966067683156L, 574377167401875275L },
                new long[] { 88902802571733L, 229619176668713819L, 931811048770190271L },
                new long[] { 25267680276078L, 3013678680992525L, 463401061632866526L },
                new long[] { 36270218540497L, 705585629946580636L, 237993140746255962L },
                new long[] { 24074486908231L, 174977792365466257L, 246923322810917141L },
                new long[] { 91430288197103L, 288597806669760892L, 938638285025333403L },
                new long[] { 34413065578016L, 127815921815005561L, 868836468420090470L },
                new long[] { 23053081172816L, 430487623791969842L, 487255036638784583L },
                new long[] { 11487696932154L, 902810424020138335L, 124462181441773470L },
                new long[] { 63783299490636L, 259666498587618221L, 225225512486764533L },
                new long[] { 67720186971698L, 544312419572409913L, 959008952310058822L },
                new long[] { 95548255300263L, 520781532296796249L, 481641953868218774L },
                new long[] { 76085327132285L, 723110424803456124L, 867697064507995236L },
                new long[] { 37774242535411L, 291684276865538926L, 205024910326572967L },
                new long[] { 23701913275725L, 675285653248258265L, 463092207058596522L },
                new long[] { 29798860272258L, 331913126375147341L, 994889534765745501L },
                new long[] { 18495701454879L, 288984856827726077L, 713721403798879715L },
                new long[] { 38298203783031L, 473527721580348144L, 513491373226651381L },
                new long[] { 34829543829199L, 918180278916522431L, 27392251122869539L },
                new long[] { 40957953066405L, 232632538044100059L, 654939159879593635L },
                new long[] { 29746152185502L, 371307642255121183L, 693803580388584903L },
                new long[] { 41698116222072L, 977186158236678424L, 689157993532961922L },
                new long[] { 62467957194401L, 269043877107275048L, 102390895523597457L },
                new long[] { 23189706772547L, 915061505504953922L, 979530901129967519L },
                new long[] { 86188088225875L, 314529584099251203L, 829009407770775672L },
                new long[] { 11306739708304L, 724483816533873502L, 340845647058077308L },
                new long[] { 82959174767140L, 363198008187129011L, 875491310547126581L },
                new long[] { 97623331044818L, 386269515456334926L, 366572897563400500L },
                new long[] { 42846280183517L, 70527831839425882L, 145521227251250327L },
                new long[] { 55121603546981L, 200581762165212827L, 652751691296897789L },
                new long[] { 32238195734329L, 339946437501907836L, 945765883352399886L },
                new long[] { 75506164965184L, 775180738168837861L, 91527357929701337L },
                new long[] { 62177842752192L, 623401942399639168L, 44983993173312731L },
                new long[] { 32924185707147L, 349566916674687634L, 660915035914677504L },
                new long[] { 99518671430235L, 219628894890102423L, 325116913619626622L },
                new long[] { 73267460800591L, 547471830798392868L, 535206946944540724L },
                new long[] { 76841822524674L, 417161514036427982L, 273348055556214818L },
                new long[] { 97142617910342L, 598647204516893989L, 422179826088076852L },
                new long[] { 87783646182799L, 346313767754307809L, 363333018982642090L },
                new long[] { 10848802521674L, 670883215120185883L, 543223812876952786L },
                new long[] { 71329612474782L, 464538636993009049L, 310363619763878039L },
                new long[] { 62184073572399L, 794223406235393808L, 339651327408011116L },
                new long[] { 66627891981488L, 87797941876876144L, 230030984490851411L },
                new long[] { 60661826293682L, 836764744779239180L, 335110989069790714L },
                new long[] { 85786944089552L, 990653640447425576L, 83659976645795096L },
                new long[] { 66024396409905L, 389607120198219976L, 47599490197230297L },
                new long[] { 64913982680032L, 973156037120041377L, 903785566085089252L },
                new long[] { 16730939319872L, 750275468906903707L, 539413042652315011L },
                new long[] { 94809377245048L, 795150954100921645L, 863754710598436791L },
                new long[] { 78639167021187L, 492431995700641917L, 969777599028300699L },
                new long[] { 15368713711936L, 614952811305876380L, 278410754449733078L },
                new long[] { 40789923115535L, 562561142322423255L, 33685442488917353L },
                new long[] { 44889911501440L, 648020369068063960L, 672322193204149535L },
                new long[] { 41503128880339L, 536053299340368006L, 977710650566631954L },
                new long[] { 81234880673210L, 146739058568557934L, 581403627822703280L },
                new long[] { 82616570773948L, 327592232845941706L, 525094512325230608L },
                new long[] { 22918802058777L, 319719839450180888L, 72429661980811197L },
                new long[] { 77158542502016L, 545090413245809786L, 882778948721859617L },
                new long[] { 72107838435069L, 186155435662884062L, 257473692284509516L },
                new long[] { 20849603980134L, 1723930671666823L, 555245252804609722L },
                new long[] { 53503534226472L, 524250874054075591L, 789781264330331690L }, };
        long ten18 = 1000000000000000000L;
        long ten10 = 10000000000L;
        long high = 0, med = 0, low = 0;
        for (byte i = 0; i < 100; ++i) {
            low += numbers[i][2];
            med += numbers[i][1];
            high += numbers[i][0];
            if (low > ten18) {
                med += low / ten18;
                low %= ten18;
            }
            if (med > ten18) {
                high += med / ten18;
                med %= ten18;
            }
        }
        while (high > ten10)
            high /= 10;
        return high;
    }
}