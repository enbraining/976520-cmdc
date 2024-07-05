import java.io.*;
import java.time.LocalTime;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));

        int numberOfStudents = Integer.parseInt(bufferedReader.readLine());

        StringTokenizer tokenizedCommands = new StringTokenizer(new StringBuilder(bufferedReader.readLine()).reverse().toString());
        Deque<Integer> studentLine = new LinkedList<>();

        for (int studentNumber = 1; studentNumber <= numberOfStudents; studentNumber++) {
            int command = Integer.parseInt(tokenizedCommands.nextToken());

            if (command == 1) {
                studentLine.addFirst(studentNumber);
            } else if (command == 2) {
                int firstStudent = studentLine.removeFirst();
                studentLine.addFirst(studentNumber);
                studentLine.addFirst(firstStudent);
            } else {
                studentLine.addLast(studentNumber);
            }
        }

        StringBuilder resultBuilder = new StringBuilder();
        while (!studentLine.isEmpty()) {
            resultBuilder.append(studentLine.removeFirst()).append(" ");
        }

        System.out.println(resultBuilder);
    }
}
