#define private public
#include <bitset>
#undef private

#include <bits/stdc++.h>
using namespace std;
#include <x86intrin.h> //어셈블리어 명령어 호출

template<size_t NumberOfWords> void PerformSubtraction(_Base_bitset<NumberOfWords>& BitsetA, const _Base_bitset<NumberOfWords>& BitsetB) {
	for (int Index = 0, Carry = 0; Index < NumberOfWords; Index++) 
        Carry = _subborrow_u64(Carry, BitsetA._M_w[Index], BitsetB._M_w[Index], (unsigned long long*) &BitsetA._M_w[Index]);
}
template<> void PerformSubtraction(_Base_bitset<1>& BitsetA, const _Base_bitset<1>& BitsetB) { 
    BitsetA._M_w -= BitsetB._M_w; 
}
template<size_t NumberOfBits> bitset<NumberOfBits>& operator-=(bitset<NumberOfBits>& BitsetA, const bitset<NumberOfBits>& BitsetB) { 
    return PerformSubtraction(BitsetA, BitsetB), BitsetA; 
}
template<size_t NumberOfBits> inline bitset<NumberOfBits> operator-(const bitset<NumberOfBits>& BitsetA, const bitset<NumberOfBits>& BitsetB) { 
    bitset<NumberOfBits> ResultBitset(BitsetA); 
    return ResultBitset -= BitsetB; 
}

template<size_t BitsetSize = 50'000>
int CalculateLongestCommonSubsequence(const string& StringA, const string& StringB) {
    bitset<BitsetSize> BitsetD, BitsetX, CharacterBitsets[26];
    for (int Index = 0; Index < StringB.size(); Index++) 
        CharacterBitsets[StringB[Index] - 'A'][Index] = 1;
    
    for (int Index = 0; Index < StringA.size(); Index++) {
        BitsetX = CharacterBitsets[StringA[Index] - 'A'] | BitsetD; 
        BitsetD <<= 1, BitsetD[0] = 1;
        BitsetD = BitsetX & (BitsetX ^ (BitsetX - BitsetD));
    }
    return BitsetD.count();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string FirstString, SecondString; 
    cin >> FirstString >> SecondString;
    cout << CalculateLongestCommonSubsequence(FirstString, SecondString) << '\n';
}
