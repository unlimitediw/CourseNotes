# cook your code here
class WordCounter

    def initialize(file_name)

        @file = File.read("test.txt")
        puts @file
        #@file = "nanasaki why do you love swim why why why?"
    end
    def count()
        return @file.split.length
    end
    def uniq_count()
        return @file.split.uniq.length
    end
    def frequency()
        wordList = @file.split
        wordDic = Hash.new
        i = 0
        loop do
            if i == wordList.length
                break
            end
            if wordDic.has_key?(wordList[i])
                wordDic[wordList[i]] += 1
            else
                wordDic[wordList[i]] = 1
            end
            i += 1
        end
        return wordDic
    end
end

counter = WordCounter.new("")
print counter.frequency(),"\n"
print counter.count() ,"\n"
print counter.uniq_count()
