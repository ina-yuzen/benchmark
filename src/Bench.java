import java.util.Arrays;

public class Bench {
    private static int count = 100000;
    private static long concat_using_plus() {
        long a, b;
        String k = "abcde";
        a = System.nanoTime();
        for (int i = 0; i < count; i++) {
            k += "abcde";
        }
        b = System.nanoTime();
        return b - a;
    }

    private static long concat_using_method() {
        long a, b;
        String k = "abcde";
        a = System.nanoTime();
        for (int i = 0; i < count; i++) {
            k.concat("abcde");
        }
        b = System.nanoTime();
        return b - a;
    }

    private static long concat_using_stringbuffer() {
        long a, b;
        String k = "abcde";
        StringBuffer sb = new StringBuffer(k);
        a = System.nanoTime();
        for (int i = 0; i < count; i++) {
            sb.append("abcde");
        }
        b = System.nanoTime();
        return b - a;
    }

    private static long concat_using_stringbuilder() {
        long a, b;
        String k = "abcde";
        StringBuilder sb = new StringBuilder(k);
        a = System.nanoTime();
        for (int i = 0; i < count; i++) {
            sb.append("abcde");
        }
        b = System.nanoTime();
        return b - a;
    }

    public static void main(String[] args){
        int times = 100;
        long[] plus = new long[times];
        long[] method = new long[times];
        long[] stringbuffer = new long[times];
        long[] stringbuilder = new long[times];

        System.out.println("Try " + times + " times for each way...");

        for (int i = 0; i < times; i++) {
            plus[i] = concat_using_plus();
            method[i] = concat_using_method();
            stringbuffer[i] = concat_using_stringbuffer();
            stringbuilder[i] = concat_using_stringbuilder();
        }

        Arrays.sort(plus);
        Arrays.sort(method);
        Arrays.sort(stringbuffer);
        Arrays.sort(stringbuilder);

        System.out.println("Done. Results are in nano seconds.\n");

        print_result(times, plus, "plus");
        print_result(times, method, "String.concat");
        print_result(times, stringbuffer, "StringBuffer.append");
        print_result(times, stringbuilder, "StringBuilder.append");
    }

    private static void print_result(int times, long[] array, String label) {
        System.out.println("** concat using " + label + " **");
        long sum = 0;
        for (int i = 0; i < times; i++) {
            sum += array[i];
        }
        double average = (double) sum / times;

        sum = 0;
        for (int i = 0; i < times; i++) {
            sum += (array[i] - average) * (array[i] - average);
        }
        double sd = Math.sqrt((double) sum / times);

        System.out.println("Average: \t" + average);
        System.out.println("Standard deviation: \t" + sd);
        System.out.println("Max: \t" + array[times - 1]);
        System.out.println("Min: \t" + array[0]);
        System.out.println("Median: \t" + (times % 2 == 0 ? (array[times / 2] + array[times / 2 - 1]) / 2.0d : array[times / 2]));
    }
}