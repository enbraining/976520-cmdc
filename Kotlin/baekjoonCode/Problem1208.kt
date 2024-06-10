//1208 부분수여ㅑㄹ의 합 2

val sumFrequencyMap = mutableMapOf<Long, Long>()
var count = 0L

fun calculatePrefixSums(index: Int, end: Int, inputArray: LongArray, currentSum: Long) {
    if (index == end) {
        sumFrequencyMap[currentSum] = sumFrequencyMap.getOrDefault(currentSum, 0) + 1
        return
    }
    calculatePrefixSums(index + 1, end, inputArray, currentSum + inputArray[index])
    calculatePrefixSums(index + 1, end, inputArray, currentSum)
}

fun calculateLeftSums(index: Int, end: Int, inputArray: LongArray, currentSum: Long, targetSum: Int) {
    if (index == end) {
        count += sumFrequencyMap.getOrDefault(targetSum - currentSum, 0)
        return
    }
    calculateLeftSums(index + 1, end, inputArray, currentSum + inputArray[index], targetSum)
    calculateLeftSums(index + 1, end, inputArray, currentSum, targetSum)
}

fun main() = with(System.out.bufferedWriter()) {
    val bufferedReader = System.`in`.bufferedReader()
    val (n, targetSum) = bufferedReader.readLine().split(' ').map { it.toInt() }
    val inputArray = bufferedReader.readLine().split(' ').map { it.toLong() }.toLongArray()

    calculatePrefixSums(n / 2, n, inputArray, 0)
    calculateLeftSums(0, n / 2, inputArray, 0, targetSum)

    if (targetSum == 0) count--

    write("$count")
    close()
}
