! Project Euler Problem 13
!
! Problem:
!
! Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
! 37107287533902102798797998220837590246510135740250
! 46376937677490009712648124896970078050417018260538
! 74324986199524741059474233309513058123726617309629
! 91942213363574161572522430563301811072406154908250
! 23067588207539346171171980310421047513778063246676
! 89261670696623633820136378418383684178734361726757
! 28112879812849979408065481931592621691275889832738
! 44274228917432520321923589422876796487670272189318
! 47451445736001306439091167216856844588711603153276
! 70386486105843025439939619828917593665686757934951
! 62176457141856560629502157223196586755079324193331
! 64906352462741904929101432445813822663347944758178
! 92575867718337217661963751590579239728245598838407
! 58203565325359399008402633568948830189458628227828
! 80181199384826282014278194139940567587151170094390
! 35398664372827112653829987240784473053190104293586
! 86515506006295864861532075273371959191420517255829
! 71693888707715466499115593487603532921714970056938
! 54370070576826684624621495650076471787294438377604
! 53282654108756828443191190634694037855217779295145
! 36123272525000296071075082563815656710885258350721
! 45876576172410976447339110607218265236877223636045
! 17423706905851860660448207621209813287860733969412
! 81142660418086830619328460811191061556940512689692
! 51934325451728388641918047049293215058642563049483
! 62467221648435076201727918039944693004732956340691
! 15732444386908125794514089057706229429197107928209
! 55037687525678773091862540744969844508330393682126
! 18336384825330154686196124348767681297534375946515
! 80386287592878490201521685554828717201219257766954
! 78182833757993103614740356856449095527097864797581
! 16726320100436897842553539920931837441497806860984
! 48403098129077791799088218795327364475675590848030
! 87086987551392711854517078544161852424320693150332
! 59959406895756536782107074926966537676326235447210
! 69793950679652694742597709739166693763042633987085
! 41052684708299085211399427365734116182760315001271
! 65378607361501080857009149939512557028198746004375
! 35829035317434717326932123578154982629742552737307
! 94953759765105305946966067683156574377167401875275
! 88902802571733229619176668713819931811048770190271
! 25267680276078003013678680992525463401061632866526
! 36270218540497705585629946580636237993140746255962
! 24074486908231174977792365466257246923322810917141
! 91430288197103288597806669760892938638285025333403
! 34413065578016127815921815005561868836468420090470
! 23053081172816430487623791969842487255036638784583
! 11487696932154902810424020138335124462181441773470
! 63783299490636259666498587618221225225512486764533
! 67720186971698544312419572409913959008952310058822
! 95548255300263520781532296796249481641953868218774
! 76085327132285723110424803456124867697064507995236
! 37774242535411291684276865538926205024910326572967
! 23701913275725675285653248258265463092207058596522
! 29798860272258331913126375147341994889534765745501
! 18495701454879288984856827726077713721403798879715
! 38298203783031473527721580348144513491373226651381
! 34829543829199918180278916522431027392251122869539
! 40957953066405232632538044100059654939159879593635
! 29746152185502371307642255121183693803580388584903
! 41698116222072977186158236678424689157993532961922
! 62467957194401269043877107275048102390895523597457
! 23189706772547915061505504953922979530901129967519
! 86188088225875314529584099251203829009407770775672
! 11306739708304724483816533873502340845647058077308
! 82959174767140363198008187129011875491310547126581
! 97623331044818386269515456334926366572897563400500
! 42846280183517070527831839425882145521227251250327
! 55121603546981200581762165212827652751691296897789
! 32238195734329339946437501907836945765883352399886
! 75506164965184775180738168837861091527357929701337
! 62177842752192623401942399639168044983993173312731
! 32924185707147349566916674687634660915035914677504
! 99518671430235219628894890102423325116913619626622
! 73267460800591547471830798392868535206946944540724
! 76841822524674417161514036427982273348055556214818
! 97142617910342598647204516893989422179826088076852
! 87783646182799346313767754307809363333018982642090
! 10848802521674670883215120185883543223812876952786
! 71329612474782464538636993009049310363619763878039
! 62184073572399794223406235393808339651327408011116
! 66627891981488087797941876876144230030984490851411
! 60661826293682836764744779239180335110989069790714
! 85786944089552990653640447425576083659976645795096
! 66024396409905389607120198219976047599490197230297
! 64913982680032973156037120041377903785566085089252
! 16730939319872750275468906903707539413042652315011
! 94809377245048795150954100921645863754710598436791
! 78639167021187492431995700641917969777599028300699
! 15368713711936614952811305876380278410754449733078
! 40789923115535562561142322423255033685442488917353
! 44889911501440648020369068063960672322193204149535
! 41503128880339536053299340368006977710650566631954
! 81234880673210146739058568557934581403627822703280
! 82616570773948327592232845941706525094512325230608
! 22918802058777319719839450180888072429661980811197
! 77158542502016545090413245809786882778948721859617
! 72107838435069186155435662884062257473692284509516
! 20849603980134001723930671666823555245252804609722
! 53503534226472524250874054075591789781264330331690

module Problem0013
    implicit none

contains

    integer(kind=8) function p0013() result(answer)
        integer(kind=8), dimension(100, 3) :: numbers
        integer(kind=8), dimension(3) :: arr
        integer(kind=8) :: ten18 = 1000000000000000000_8
        integer(kind=8) :: ten10 = 10000000000_8
        integer :: i, j

        ! Manually initialize the grid
        data numbers / &
            37107287533902_8, 102798797998220837_8, 590246510135740250_8, &
            46376937677490_8,   9712648124896970_8,  78050417018260538_8, &
            74324986199524_8, 741059474233309513_8,  58123726617309629_8, &
            91942213363574_8, 161572522430563301_8, 811072406154908250_8, &
            23067588207539_8, 346171171980310421_8,  47513778063246676_8, &
            89261670696623_8, 633820136378418383_8, 684178734361726757_8, &
            28112879812849_8, 979408065481931592_8, 621691275889832738_8, &
            44274228917432_8, 520321923589422876_8, 796487670272189318_8, &
            47451445736001_8, 306439091167216856_8, 844588711603153276_8, &
            70386486105843_8,  25439939619828917_8, 593665686757934951_8, &
            62176457141856_8, 560629502157223196_8, 586755079324193331_8, &
            64906352462741_8, 904929101432445813_8, 822663347944758178_8, &
            92575867718337_8, 217661963751590579_8, 239728245598838407_8, &
            58203565325359_8, 399008402633568948_8, 830189458628227828_8, &
            80181199384826_8, 282014278194139940_8, 567587151170094390_8, &
            35398664372827_8, 112653829987240784_8, 473053190104293586_8, &
            86515506006295_8, 864861532075273371_8, 959191420517255829_8, &
            71693888707715_8, 466499115593487603_8, 532921714970056938_8, &
            54370070576826_8, 684624621495650076_8, 471787294438377604_8, &
            53282654108756_8, 828443191190634694_8,  37855217779295145_8, &
            36123272525000_8, 296071075082563815_8, 656710885258350721_8, &
            45876576172410_8, 976447339110607218_8, 265236877223636045_8, &
            17423706905851_8, 860660448207621209_8, 813287860733969412_8, &
            81142660418086_8, 830619328460811191_8,  61556940512689692_8, &
            51934325451728_8, 388641918047049293_8, 215058642563049483_8, &
            62467221648435_8,  76201727918039944_8, 693004732956340691_8, &
            15732444386908_8, 125794514089057706_8, 229429197107928209_8, &
            55037687525678_8, 773091862540744969_8, 844508330393682126_8, &
            18336384825330_8, 154686196124348767_8, 681297534375946515_8, &
            80386287592878_8, 490201521685554828_8, 717201219257766954_8, &
            78182833757993_8, 103614740356856449_8,  95527097864797581_8, &
            16726320100436_8, 897842553539920931_8, 837441497806860984_8, &
            48403098129077_8, 791799088218795327_8, 364475675590848030_8, &
            87086987551392_8, 711854517078544161_8, 852424320693150332_8, &
            59959406895756_8, 536782107074926966_8, 537676326235447210_8, &
            69793950679652_8, 694742597709739166_8, 693763042633987085_8, &
            41052684708299_8,  85211399427365734_8, 116182760315001271_8, &
            65378607361501_8,  80857009149939512_8, 557028198746004375_8, &
            35829035317434_8, 717326932123578154_8, 982629742552737307_8, &
            94953759765105_8, 305946966067683156_8, 574377167401875275_8, &
            88902802571733_8, 229619176668713819_8, 931811048770190271_8, &
            25267680276078_8,   3013678680992525_8, 463401061632866526_8, &
            36270218540497_8, 705585629946580636_8, 237993140746255962_8, &
            24074486908231_8, 174977792365466257_8, 246923322810917141_8, &
            91430288197103_8, 288597806669760892_8, 938638285025333403_8, &
            34413065578016_8, 127815921815005561_8, 868836468420090470_8, &
            23053081172816_8, 430487623791969842_8, 487255036638784583_8, &
            11487696932154_8, 902810424020138335_8, 124462181441773470_8, &
            63783299490636_8, 259666498587618221_8, 225225512486764533_8, &
            67720186971698_8, 544312419572409913_8, 959008952310058822_8, &
            95548255300263_8, 520781532296796249_8, 481641953868218774_8, &
            76085327132285_8, 723110424803456124_8, 867697064507995236_8, &
            37774242535411_8, 291684276865538926_8, 205024910326572967_8, &
            23701913275725_8, 675285653248258265_8, 463092207058596522_8, &
            29798860272258_8, 331913126375147341_8, 994889534765745501_8, &
            18495701454879_8, 288984856827726077_8, 713721403798879715_8, &
            38298203783031_8, 473527721580348144_8, 513491373226651381_8, &
            34829543829199_8, 918180278916522431_8,  27392251122869539_8, &
            40957953066405_8, 232632538044100059_8, 654939159879593635_8, &
            29746152185502_8, 371307642255121183_8, 693803580388584903_8, &
            41698116222072_8, 977186158236678424_8, 689157993532961922_8, &
            62467957194401_8, 269043877107275048_8, 102390895523597457_8, &
            23189706772547_8, 915061505504953922_8, 979530901129967519_8, &
            86188088225875_8, 314529584099251203_8, 829009407770775672_8, &
            11306739708304_8, 724483816533873502_8, 340845647058077308_8, &
            82959174767140_8, 363198008187129011_8, 875491310547126581_8, &
            97623331044818_8, 386269515456334926_8, 366572897563400500_8, &
            42846280183517_8,  70527831839425882_8, 145521227251250327_8, &
            55121603546981_8, 200581762165212827_8, 652751691296897789_8, &
            32238195734329_8, 339946437501907836_8, 945765883352399886_8, &
            75506164965184_8, 775180738168837861_8,  91527357929701337_8, &
            62177842752192_8, 623401942399639168_8,  44983993173312731_8, &
            32924185707147_8, 349566916674687634_8, 660915035914677504_8, &
            99518671430235_8, 219628894890102423_8, 325116913619626622_8, &
            73267460800591_8, 547471830798392868_8, 535206946944540724_8, &
            76841822524674_8, 417161514036427982_8, 273348055556214818_8, &
            97142617910342_8, 598647204516893989_8, 422179826088076852_8, &
            87783646182799_8, 346313767754307809_8, 363333018982642090_8, &
            10848802521674_8, 670883215120185883_8, 543223812876952786_8, &
            71329612474782_8, 464538636993009049_8, 310363619763878039_8, &
            62184073572399_8, 794223406235393808_8, 339651327408011116_8, &
            66627891981488_8,  87797941876876144_8, 230030984490851411_8, &
            60661826293682_8, 836764744779239180_8, 335110989069790714_8, &
            85786944089552_8, 990653640447425576_8,  83659976645795096_8, &
            66024396409905_8, 389607120198219976_8,  47599490197230297_8, &
            64913982680032_8, 973156037120041377_8, 903785566085089252_8, &
            16730939319872_8, 750275468906903707_8, 539413042652315011_8, &
            94809377245048_8, 795150954100921645_8, 863754710598436791_8, &
            78639167021187_8, 492431995700641917_8, 969777599028300699_8, &
            15368713711936_8, 614952811305876380_8, 278410754449733078_8, &
            40789923115535_8, 562561142322423255_8,  33685442488917353_8, &
            44889911501440_8, 648020369068063960_8, 672322193204149535_8, &
            41503128880339_8, 536053299340368006_8, 977710650566631954_8, &
            81234880673210_8, 146739058568557934_8, 581403627822703280_8, &
            82616570773948_8, 327592232845941706_8, 525094512325230608_8, &
            22918802058777_8, 319719839450180888_8,  72429661980811197_8, &
            77158542502016_8, 545090413245809786_8, 882778948721859617_8, &
            72107838435069_8, 186155435662884062_8, 257473692284509516_8, &
            20849603980134_8,   1723930671666823_8, 555245252804609722_8, &
            53503534226472_8, 524250874054075591_8, 789781264330331690_8 /

        arr = (/ 0, 0, 0 /)
        do i = 1, 100
            do j = 1, 3
                arr(j) = arr(j) + numbers(i, j);
            end do
            do j = 2, 1, -1
                if (arr(j) > ten18) then
                    arr(j - 1) = arr(j - 1) + arr(j) / ten18;
                    arr(j) = arr(j) % ten18;
                end if
            end do
        end do
        do while (arr(1) > ten10)
            arr(1) = arr(1) / 10
        end do
        answer = arr(1)
    end function p0013
end module Problem0013
