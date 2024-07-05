import java.math.BigInteger

fun main() = with(System.`in`.bufferedReader()) {
    val bufferedWriterForOutput = System.out.bufferedWriter()
    val numberOfTestCases = readLine().toInt()
    repeat(numberOfTestCases) {
        val inputLine = readLine().split(" ").map { it.toInt() }
        val numberOfCombinations = calculateCombination(inputLine[1], inputLine[0])
        bufferedWriterForOutput.write("$numberOfCombinations\n")
    }
    bufferedWriterForOutput.close()
}

fun calculateCombination(totalElements: Int, chooseElements: Int): BigInteger {
    var currentElement = totalElements
    val minChooseOrRemainingElements = minOf(chooseElements, totalElements - chooseElements)
    var combinationResult = BigInteger.ONE
    var factorialOfChooseElements = 1L
    // nPk
    repeat(minChooseOrRemainingElements) {
        combinationResult = combinationResult.multiply(currentElement--.toBigInteger())
    }
    // k!
    for (i in 2..minChooseOrRemainingElements) {
        factorialOfChooseElements *= i
    }
    return combinationResult.divide(factorialOfChooseElements.toBigInteger())
}
