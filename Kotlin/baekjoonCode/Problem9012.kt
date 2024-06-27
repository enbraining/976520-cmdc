import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.*

fun main() = with(BufferedReader(InputStreamReader(System.`in`))){
    val numberOfTestCases = readLine().toInt()

    for(testCaseIndex in 0 until numberOfTestCases) {
        val inputString = readLine()
        checkParenthesesBalance(inputString)
    }
}

fun checkParenthesesBalance(inputString: String){
    val parenthesesStack = Stack<Char>()

    for(character in inputString){
        if(character == '('){
            parenthesesStack.add(character)
        }
        else if(character == ')'){
            if(parenthesesStack.isEmpty()){
                println("NO")
                return
            }
            if(parenthesesStack.pop() == ')'){
                println("NO")
                return
            }
        }
    }

    if(parenthesesStack.isEmpty()){
        println("YES")
    }
    else{
        println("NO")
    }
}
