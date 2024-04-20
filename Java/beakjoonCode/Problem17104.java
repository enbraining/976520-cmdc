
/*
[[8시간 삽질한 사람의 개념 정리]]
고마워요 위키백과!

* 시간 영역 time domain vs 주파수 영역 frequency domain
    시간 영역
        원본 데이터의 시간에 따른 변화를 표현하며, 일반적으로 시간축에 데이터의 크기 또는 값이 표시됩니다.
        시간 영역에서의 데이터를 통해 신호의 진폭, 주기, 주기성, 변화율 등을 분석할 수 있다.
    주파수 영역
        주파수 영역은 주파수에 따른 데이터의 변화를 표현한다.
        신호의 주파수 구성 요소를 표현하며, 주파수 축에 주파수 성분의 크기 또는 값이 표시됩니다.
        주파수 영역에서의 데이터를 통해 신호의 주파수 성분(그 성분이 어떤 강도, 진폭을 가지는지), 주파수 대역, 주파수 구성 등을 분석할 수 있다.

* 고속 푸리에 변환 vs 역 고속 푸리에 변환
    고속 푸리에 변환
        시간 영역에서 측정된 신호를 주파수 성분으로 분해!
        (굳이 왜? : 주파수 영역에서의 신호 처리는 시간 영역보다 간단하고 직관적이며, 다양한 신호 특성을 파악하는 데 도움이 된다고 한다. 나도 잘 모르겠다)
        0. 샘플링: 주어진 시간 동안 신호를 정기적으로 측정하여 디지털 형태로 변환한다.
                  이 과정에서 시간 영역의 연속적인 신호가 이산적인 샘플(연속된 아날로그 신호를 일정한 간격으로 측정하여 얻은 값)로 변환된다.
        1. 주파수 영역으로 변환: FFT 알고리즘을 사용하여 샘플링된 시간 영역의 데이터를 주파수 영역으로 변환한다.
                             이 과정에서 각 주파수 성분의 진폭과 위상을 계산한다.
        2. 변환된 주파수 영역에서 주파수 성분을 분석하여 주요 주파수, 고조파, 스펙트럼 등의 정보를 얻습니다.
    역 고속 푸리에 변환
        시간 영역의 신호를 주파수 성분으로 역변환!
        0. 고속 푸리에 변환의 과정을 거꾸로 수행한다.

0. calculateSquares 메서드에서 고속 푸리에 변환(FFT)을 사용하여 주어진 소수 생성기 배열(primeGenerator)의 제곱을 계산한다.
    0.0. 소수 생성기 배열은 주어진 길이의 배열이며, 각 요소는 1 또는 0의 값을 가진다.
         이 배열의 제곱을 계산하기 위해 일반적으로는 이산 푸리에 변환(DFT)을 사용할 수 있지만, DFT는 O(n^2)의 시간 복잡도를 가지므로 계산하기가 좀 빡세다.
         FFT를 사용하는 이유는 이를 통해 O(n log n)의 시간 복잡도로 주파수 영역에서의 제곱을 "존나게 효율적으로" 계산할 수 있기 때문이다.

1. FFT를 위한 적절한 길이의 배열을 만들기 위해 입력 배열의 크기를 2의 거듭제곱으로 조정한다.
    1.0. 분할 정복(divide and conquer) 방법을 사용하여 입력 데이터를 재귀적으로 분할하기 때문에 배열의 크기가 2의 거듭제곱이 아닌 경우에는 효율이 좀 떨어질 수 있다.
         한마디로 배열의 크기가 2의 n승 이여야 FFT를 뽕뽑을 수 있다.

2. FFT를 수행하기 위해 복소수 형태의 배열(complexNumbers)을 생성하고, 해당 배열의 실수 부분에는 입력 배열의 값을 설정한다.
    2.0. FFT는 실수값을 입력으로 받지만, 실제로는 복소수 형태로 처리되기 때문에 FFT 알고리즘을 통해 주파수 영역으로 변환할 때 복소수 공간에서의 계산이 쌉꿀마라고 할 수 있다.
    2.1. 따라서 FFT 알고리즘은 입력 데이터를 복소수 형태로 표현하여 적용해야 하기 때문에 입력 배열의 값을 복소수의 실수 부분에 설정한다.
3.0. FFT 알고리즘을 사용하여 주파수 영역에서의 계산을 수행하기 위해 삼중 중첩된 반복문을 사용했다.
    3.0. 첫 번째 반복문은 배열을 비트 리버스(각 요소의 인덱스를 이진수로 표현했을 때 비트를 역순으로 배치하는 것) 순서로 재배치한다.
    3.1. 두 번째 반복문은 주파수 영역에서 주파수 성분의 계산을 수행한다.
    3.2. 세 번째 반복문은 주파수 영역에서의 계산 결과를 시간 영역으로 다시 변환한다.
    3.3. 미리 계산된 코사인과 사인 값의 배열을 사용하여 최적화한다. (이거 안하면 시간초과 존나된다)

4. FFT를 통해 주파수 영역에서의 제곱을 계산하고 역 FFT를 사용하여 시간 영역으로 변환한다. 이렇게하면 primeGenerator의 제곱이 얻어지며, 이를 반환하여 사용하면 된다!

제대로 이해한게 아닐 수도 있어요..
*/


import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Arrays;

public class Problem17104 {

    static double[] cos;  // 코사인 값 배열
    static double[] sin;  // 사인 값 배열

    static void performFFT(double[][] complexNumbers, boolean isInverse) {  // FFT 연산 메서드
        int n = complexNumbers.length;  // 배열의 길이 계산
        int v = n >> 1;  // 중간값 계산

        for (int i = 1, rev = 0; i < n; i++) {  // 비트 리버스 순서로 배열의 요소를 재배치
            int bit = n >> 1;
            while (rev >= bit) {
                rev -= bit;
                bit >>= 1;
            }
            rev += bit;
            if (i < rev) {
                double[] tmp = complexNumbers[i];
                complexNumbers[i] = complexNumbers[rev];
                complexNumbers[rev] = tmp;
            }
        }

        for (int k = 1; k < n; k <<= 1) {  // Cooley-Tukey FFT 알고리즘 수행
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    int trigonometricIdx = v / k * j;  // 삼각 함수 인덱스 계산

                    double c = cos[trigonometricIdx];  // 코사인 값
                    double s = sin[trigonometricIdx];  // 사인 값

                    if (isInverse) s = -s;  // 역 FFT인 경우 사인 값의 부호를 변경

                    double[] complexNumber1 = complexNumbers[i + j];  // 첫 번째 복소수
                    double[] complexNumber2 = complexNumbers[i + j + k];  // 두 번째 복소수

                    double reX = complexNumber1[0];  // 첫 번째 복소수의 실수부
                    double imX = complexNumber1[1];  // 첫 번째 복소수의 허수부

                    double reY = complexNumber2[0] * c - complexNumber2[1] * s;  // 두 번째 복소수의 실수부
                    double imY = complexNumber2[0] * s + complexNumber2[1] * c;  // 두 번째 복소수의 허수부

                    complexNumber1[0] = reX + reY;  // 첫 번째 복소수의 실수부 갱신
                    complexNumber1[1] = imX + imY;  // 첫 번째 복소수의 허수부 갱신

                    complexNumber2[0] = reX - reY;  // 두 번째 복소수의 실수부 갱신
                    complexNumber2[1] = imX - imY;  // 두 번째 복소수의 허수부 갱신
                }
            }
        }

        if (isInverse) {  // 역 FFT인 경우 결과를 정규화
            for (int i = 0; i < n; i++) {
                complexNumbers[i][0] /= n;
                complexNumbers[i][1] /= n;
            }
        }
    }

    static int[] calculateSquares(int[] primeGenerator) {  // 소수 제곱 배열 계산 메서드

        int fftLength = 1;  // FFT 길이 초기화
        while (fftLength < primeGenerator.length + primeGenerator.length) fftLength <<= 1;  // FFT 길이를 설정

        int trigonometricInitLength = fftLength >> 1;  // FFT 초기 삼각 함수 길이 계산
        double angle = Math.PI / trigonometricInitLength;  // 각도 계산

        cos = new double[trigonometricInitLength];  // 삼각 함수 배열 초기화
        sin = new double[trigonometricInitLength];

        for (int i = 0; i < trigonometricInitLength; i++) {  // 삼각 함수 배열 계산
            cos[i] = Math.cos(angle * i);
            sin[i] = Math.sin(angle * i);
        }

        double[][] complexNumbers = new double[fftLength][2];  // 복소수 배열 생성
        for (int i = 0; i < primeGenerator.length; i++) {
            complexNumbers[i][0] = primeGenerator[i];
        }

        performFFT(complexNumbers, false);  // FFT 연산 수행

        for (int i = 0; i < fftLength; i++) {  // 제곱 연산 수행
            double re = complexNumbers[i][0] * complexNumbers[i][0] - complexNumbers[i][1] * complexNumbers[i][1];
            double im = complexNumbers[i][0] * complexNumbers[i][1] + complexNumbers[i][1] * complexNumbers[i][0];

            complexNumbers[i][0] = re;
            complexNumbers[i][1] = im;
        }

        performFFT(complexNumbers, true);  // 역 FFT 연산 수행
        int[] result = new int[primeGenerator.length + primeGenerator.length - 1];  // 결과 배열 생성
        for (int i = 0; i < result.length; i++) {
            result[i] = (int) Math.round(complexNumbers[i][0]);  // 복소수의 실수부만 결과 배열에 저장
        }
        return result;  // 결과 배열 반환
    }

    public static void main(String[] args) throws IOException { //예외 발생시 탈출
        BufferedReader input = new BufferedReader(new InputStreamReader(System.in));  // 입력 스트림 생성
        BufferedWriter output = new BufferedWriter(new OutputStreamWriter(System.out));  // 출력 스트림 생성

        final int LIMIT = 500_000;  // 상수 정의
        int[] primes = new int[1_000_000];  // 소수 배열 생성
        int[] primeGenerator = new int[LIMIT];  // 소수 생성기 배열 생성, p = 2a + 1

        Arrays.fill(primes, 1);  // 소수 배열을 1로 초기화

        primes[0] = primes[1] = 0;  // 0과 1은 소수가 아니므로 0으로 설정
        for (int i = 2; i * i <= primes.length; i++) {  // 에라토스테네스의 체를 이용하여 소수를 구함
            if (primes[i] == 0) continue;
            for (int ptr = i + i; ptr < primes.length; ptr += i) {
                primes[ptr] = 0;
            }
        }

        for (int i = 0; i < primes.length; i++) {  // 소수 생성기 배열 초기화
            if (primes[i] == 0) continue;
            primeGenerator[(i - 1) >> 1] = 1;  // 소수 생성기 배열의 인덱스 i에 해당하는 값을 1로 설정
        }
        primeGenerator[0] = 0;  // 0은 소수가 아니므로 0으로 설정

        int[] squares = calculateSquares(primeGenerator);  // 소수 생성기 배열의 제곱을 구함

        int numTestCases = Integer.parseInt(input.readLine());  // 테스트 케이스 수 입력
        while (numTestCases-- > 0) {
            int number = Integer.parseInt(input.readLine());  // 각 테스트 케이스의 짝수 입력

            if (number == 4) {  // 특정한 수가 4일 경우
                output.write('1');  // 결과 출력
            } else if (primes[number >> 1] == 0) {  // 입력된 수가 소수가 아닌 경우
                output.write(Integer.toString((Math.round(squares[(number >> 1) - 1])) / 2));  // 소수 제곱 배열에서 해당 수의 값을 출력
            } else {  // 입력된 수가 소수인 경우
                output.write(Integer.toString((Math.round(squares[(number >> 1) - 1]) - 1) / 2 + 1));  // 소수 제곱 배열에서 해당 수의 값을 출력
            }
            output.newLine();  // 다음 줄로 이동
        }
        output.flush();  // 출력 버퍼 비우기
    }
}
