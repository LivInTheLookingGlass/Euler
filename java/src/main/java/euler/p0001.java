package euler;

public class p0001 implements IEuler {
    @Override
    public Object answer() {
        int answer = 0;
        for (int i = 0; i < 1000; i += 3)
            answer += i;

        for (int i = 0; i < 1000; i += 5)
            answer += i;

        for (int i = 0; i < 1000; i += 15)
            answer -= i;

        return answer;
    }
}