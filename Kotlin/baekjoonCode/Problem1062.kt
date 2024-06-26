import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.*
import kotlin.collections.HashSet
import kotlin.math.max

var numberOfWords = 0
var numberOfLettersToTeach = 0
var wordList = arrayListOf<String>()
var maximumReadableWords = 0

fun main() = with(BufferedReader(InputStreamReader(System.`in`))){
    val stringTokenizer = StringTokenizer(readLine())

    numberOfWords = stringTokenizer.nextToken().toInt()
    numberOfLettersToTeach = stringTokenizer.nextToken().toInt()

    for(i in 0 until numberOfWords){
        wordList.add(readLine())
    }
    if(numberOfLettersToTeach < 5) {
        println(0)
        return
    }
    else if (numberOfLettersToTeach == 26){
        println(numberOfWords)
        return
    }

    findCombinations(hashSetOf(0,2,8,13,19), 0, 0)
    println(maximumReadableWords)
}

fun findCombinations(selectedLetters: HashSet<Int>, currentIndex: Int, currentCount: Int){
    if(currentCount == numberOfLettersToTeach - 5){
        countReadableWords(selectedLetters)
        return
    }

    for(i in currentIndex until 26){
        if (!selectedLetters.contains(i)) {
            selectedLetters.add(i)
            findCombinations(selectedLetters, i + 1, currentCount + 1)
            selectedLetters.remove(i)
        }
    }
}

fun countReadableWords(selectedLetters: HashSet<Int>){
    val usedAlphabets = Array(26) {false}
    var readableWordCount = 0

    loop@
    for(word in wordList){
        var letterCount = 0
        for(char in word){
            val alphabetIndex = (char - 'a')

            if(!selectedLetters.contains(alphabetIndex)){
                continue@loop
            }

            if(!usedAlphabets[alphabetIndex]){
                usedAlphabets[alphabetIndex] = true
                letterCount++
            }

            if(letterCount > numberOfLettersToTeach){
                continue@loop
            }
        }
        readableWordCount++ 
    }
    maximumReadableWords = max(maximumReadableWords, readableWordCount)
}
