private class Problem14003 {
    fun solution( n: Int, a: IntArray ): String {
        val indexDp = IntArray(n)
        val list = mutableListOf<Int>()
        list.add(Int.MIN_VALUE)
        for (i in 0 until n) {
            when {
                list[list.size - 1] < a[i] -> {
                    list.add(a[i])
                    indexDp[i] = list.size - 1
                }
                else -> {
                    var left = 0
                    var right = list.size - 1
                    while (left < right) {
                        val center = (left + right) / 2
                        when {
                            list[center] >= a[i] -> right = center
                            else -> left = center + 1
                        }
                    }
                    list[right] = a[i]
                    indexDp[i] = right
                }
            }
        }
        val stringBuilder = StringBuilder()
        val resultDeque = ArrayDeque<Int>()
        var index = list.size - 1
        stringBuilder.append("$index\n")
        for (i in n - 1 downTo 0) {
            if (index == indexDp[i]) {
                resultDeque.add(a[i])
                index -= 1
            }
        }
        while (resultDeque.isNotEmpty()) {
            stringBuilder.append("${resultDeque.removeLast()} ")
        }
        return stringBuilder.toString()
    }
}

private fun main() {
    val br = System.`in`.bufferedReader()
    val bw = System.out.bufferedWriter()

    val n = br.readLine().toInt()
    val a = when (n) {
        1 -> IntArray(n) { br.readLine().toInt() }
        else -> br.readLine().split(" ").map(String::toInt).toIntArray()
    }
    val solution14003 = Problem14003()
    bw.append("${solution14003.solution(n, a)}\n")
    bw.flush()
    br.close()
    bw.close()
}
