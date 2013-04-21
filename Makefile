all: tagger reformatter

tagger: NaiveTagger.cpp 
	g++ NaiveTagger.cpp -o NaiveTagger

reformatter: NaiveReformatter.cpp
	g++ NaiveReformatter.cpp -o NaiveReformatter

clean:
	rm NaiveTagger NaiveReformatter
