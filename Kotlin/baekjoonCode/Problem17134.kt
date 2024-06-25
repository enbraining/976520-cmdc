fun main() {
    val inputReader = System.`in`.bufferedReader()
    val stringBuilder = StringBuilder()
    val sievePrimeFlags = IntArray(2097152)
    val sieveSemiPrimeFlags = IntArray(2097152)
    for (index in 2 until 1_000_000) {
        sievePrimeFlags[index] = 1
    }
    for (index in 2 until 1_000_000) {
        if (sievePrimeFlags[index] == 0) {
            continue
        }
        if (index shl 1 < 1_000_000) {
            sieveSemiPrimeFlags[index shl 1] = 1
        }
            
        for (multiple in index + index until sievePrimeFlags.size step index){
            sievePrimeFlags[multiple] = 0
        }
    }
    fastFourierTransform(sievePrimeFlags)
    fastFourierTransform(sieveSemiPrimeFlags)
    for (index in sievePrimeFlags.indices) {
        sievePrimeFlags[index] = sievePrimeFlags[index] multiplyMod sieveSemiPrimeFlags[index]
    }
    fastFourierTransform(sievePrimeFlags, true)
    for (i in 0 until inputReader.readLine().toInt()) {
        stringBuilder.appendLine(sievePrimeFlags[inputReader.readLine().toInt()])
    }
    println(stringBuilder)
}

const val MODULO: Int = 469762049
const val ROOT_OF_UNITY: Int = 3

infix fun Int.multiplyMod(other: Int): Int =
    (toLong() * other % MODULO).toInt()

fun power(base: Int, exponent: Int): Int {
    var result = 1
    var pivot = base
    var exp = exponent
    while (exp > 0) {
        if (exp and 1 > 0) result = result multiplyMod pivot
        pivot = pivot multiplyMod pivot
        exp = exp shr 1
    }
    return result
}

val Int.modularInverse: Int get() = power(this, MODULO - 2)

fun fastFourierTransform(array: IntArray, inverse: Boolean = false) {
    val size = array.size
    var i = 1
    var bitReversedIndex = 0
    var temp: Int
    var omega: Int
    var evenPart: Int
    var oddPart: Int
    while (i < size) {
        var halfSize = size shr 1
        while (bitReversedIndex >= halfSize) {
            bitReversedIndex -= halfSize
            halfSize = halfSize shr 1
        }
        bitReversedIndex += halfSize
        if (i < bitReversedIndex) {
            temp = array[i]
            array[i] = array[bitReversedIndex]
            array[bitReversedIndex] = temp
        }
        i++
    }
    i = 1
    while (i < size) {
        omega = power(if (inverse) ROOT_OF_UNITY.modularInverse else ROOT_OF_UNITY, MODULO / i shr 1)
        bitReversedIndex = 0
        while (bitReversedIndex < size) {
            var twiddleFactor = 1
            var componentIndex = 0
            while (componentIndex < i) {
                oddPart = array[i or bitReversedIndex or componentIndex] multiplyMod twiddleFactor
                array[i or bitReversedIndex or componentIndex] = array[bitReversedIndex or componentIndex] - oddPart
                if (array[i or bitReversedIndex or componentIndex] < 0) {
                    array[i or bitReversedIndex or componentIndex] += MODULO
                }
                array[bitReversedIndex or componentIndex] += oddPart
                if (array[bitReversedIndex or componentIndex] >= MODULO) {
                    array[bitReversedIndex or componentIndex] -= MODULO
                }
                twiddleFactor = twiddleFactor multiplyMod omega
                componentIndex++
            }
            bitReversedIndex += i shl 1
        }
        i = i shl 1
    }
    if (inverse) {
        val sizeInverse = size.modularInverse
        for (index in array.indices) {
            array[index] = array[index] multiplyMod sizeInverse
        }
    }
}
