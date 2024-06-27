fun main() {
    //표준입출력
    val bufferedReader = System.`in`.bufferedReader()
    val bufferedWriter = System.out.bufferedWriter()

    // 한줄로된 입력ㅇ에서 공백을 기준으로 세 개의 Long변수로 split 할당
    val (a, b, c) = bufferedReader.readLine().split(' ').map { it.toLong() }

    // powerModulus함수에 넣은 결과를 BufferedWriter로 ㄱㄱ
    bufferedWriter.write("${powerModulus(a, b, c)}")
    // BufferedWriter의 버퍼를 비워서 출력
    bufferedWriter.flush()

    bufferedReader.close()
    bufferedWriter.close()
}


fun powerModulus(base: Long, exponent: Long, mod: Long): Long {
    return when(exponent) {
        0L -> 1 // 지수가 0이면, 1반환 base^0 = 1
        1L -> base % mod // 지수가 1이면, base를 mod로 나눈 나머지 반환 base^1 = base % mod
        else -> {
            // 지수가 2의배수(짝수)면 계속 나눠서 지수를 줄임
            val n = powerModulus(base, exponent / 2, mod)

            if(exponent % 2 == 0L) {
                (n * n) % mod 
            } else {
                ((n * n) % mod) * base % mod 
            }
        }
    }
}
