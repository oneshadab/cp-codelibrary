#include <bits/stdc++.h>

using namespace std;

struct BitStream {
    const int MAX_CAP = 8;

    vector<bool> bits;
    int start;

    BitStream() : BitStream("") {}

    BitStream(string s) {
        start = 0;
        for (auto ch: s) {
            push(ch, 8);
        }
    }

    void push(int n, int bit_width) {
        for (int i = bit_width - 1; i >= 0; i--) {
            bits.push_back(get_nth_bit(n, i));
        }
    }

    int pop(int bit_width) {
        int n = 0;
        for (int i = 0; i < bit_width; i++) {
            n = (n << 1) | bits[start];
            start++;
        }
        return n;
    }

    int get_nth_bit(int n, int nth) {
        return (n >> nth) & 1;
    }

    string str() {
        string s;
        for(int i = 0; i < bits.size(); i++) {
            if (i % 8 == 0) {
                s.push_back(0);
            }
            s[s.size() - 1] <<= 1;
            s[s.size() - 1] |= bits[i];
        }
        for(int i = bits.size(); i % 8 != 0; i++) {
            s[s.size() - 1] <<= 1;
        }
        return s;
    }
};

struct Compressor {
    string dictionary;
    int max_window, max_length;
    int window_bitwidth, length_bitwidth, symbol_bitwidth;

    Compressor() {}

    Compressor(string dictionary, int max_window = 1023, int max_length = 255) {
        this->dictionary = dictionary;
        this->max_window = max_window;
        this->max_length = max_length;

        this->window_bitwidth = get_bits_for(max_window);
        this->length_bitwidth = get_bits_for(max_length);
        this->symbol_bitwidth = get_bits_for(dictionary.length());
    }

    string compress(string original) {
        string s = original + dictionary[0];

        BitStream bs;
        for(int i = 0; i < s.length(); i++) {
            int max_match = 0, diff = 0;

            for(int j = max(0, i - max_window); j < i; j++) {
                int match = 0;
                for(int x = i, y = j; x < s.length() && y < i && s[x] == s[y]; x++, y++) {
                    match++;
                }
                if (max_match < match) {
                    max_match = match;
                    diff = (i - j);
                }
            }

            max_match = min(max_match, max_length);

            bs.push(diff, window_bitwidth);
            bs.push(max_match, length_bitwidth);
            bs.push(get_symbol_index(s[i+max_match]), symbol_bitwidth);

            i += max_match;
        }

        bs.push(0, window_bitwidth);
        bs.push(0, length_bitwidth);
        bs.push(0, symbol_bitwidth);

        return bs.str();
    }

    string decompress(string compressed) {
        BitStream bs(compressed);

        string uncompressed;
        for(int i = 0; ; i++) {
            int diff = bs.pop(window_bitwidth);
            int match = bs.pop(length_bitwidth);
            int symbol_index = bs.pop(symbol_bitwidth);
            char symbol = dictionary[symbol_index];

            for (int i = 0, startIndex = uncompressed.size() - diff; i < match; i++) {
                uncompressed.push_back(uncompressed[startIndex + i]);
            }

            if (symbol_index != 0) {
                uncompressed.push_back(symbol);
            }
            else {
                break; // Null symbol found
            }
        }
        return uncompressed;
    }

    int get_symbol_index(char symbol) {
        return find(dictionary.begin(), dictionary.end(), symbol) - dictionary.begin();
    }
        
    int get_bits_for(int n) {
        return 32 - __builtin_clz(n);
    }
};

struct VectorCompress {
    Compressor compressor;

    VectorCompress() {
        compressor = Compressor("$,0123456789");
    }

    string compress(vector<int> vec) {
        return compressor.compress(vec2string(vec));
    }

    vector<int> decompress(string compressed) {
        return string2vec(compressor.decompress(compressed));
    }

    string vec2string(vector<int> vec) {
        stringstream ss;
        for (auto x: vec) {
            ss << x << ",";
        }
        return ss.str();
    }

    vector<int> string2vec(string s) {
        vector<int> v;
        int x = 0;
        for(auto ch: s) {
            if (ch == ',') {
                v.push_back(x);
                x = 0;
            }
            else {
                x = (x * 10) + (ch - '0');
            }
        }
        return v;
    }
    
};

/***********************************************************************************************************
    EXAMPLE USAGE
***********************************************************************************************************/

vector<int> sieve(int max_num) {
    auto is_prime = new bool[max_num + 1];
    fill(is_prime, is_prime + max_num + 1, true);
    int lim = sqrt(max_num);
    for(int i = 2; i <= lim; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= max_num; j += i) {
                is_prime[j] = false;
            }
        }
    }

    vector<int> primes;
    for(int i = 2; i <= max_num; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

int main() {
    vector<int> primes = sieve(1000000);

    auto vc = VectorCompress();

    string uncompressed = vc.vec2string(primes);
    string compressed = vc.compress(primes);

    cout << "uncompressed = " << uncompressed.length() << " " << "compressed = " << compressed.length() << "\n";
    cout << "Ratio = " << (compressed.length() / double(uncompressed.length())) << "\n";
    assert (primes == vc.decompress(compressed));
}