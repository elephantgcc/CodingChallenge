===================================================================
CodingChallenge for Apertium GSoC 2013, "Sliding-window Pos Tagger"
===================================================================

Usage:
======
1. produce two executables: NaiveTagger, NaiveReformatter
    make


2. test NaiveTagger for Task1 (filtering):
    ./NaiveTagger -r < example_morph_analysis > example_morph_analysis.tagged

If the input is:
^I/I<num><mf><sg>/prpers<prn><subj><p1><mf><sg>$ ^have/have<vbhaver><inf>/have<vbhaver><pres>/have<vblex><inf>/have<vblex><pres>$ ^seen/see<vblex><pp>$ ^it/prpers<prn><subj><p3><nt><sg>/prpers<prn><obj><p3><nt><sg>$^./.<sent>$

The output should be:
I.num.mf.sg have.vbhaver.pres see.vblex.pp prpers.prn.subj.p3.nt.sg ..sent


3. test NaiveReformatter for Task2 (converting):
    ./NaiveReformatter < example_morph_analysis.tagged > example_morph_analysis.tagged.reformatted

If the input is:
I.num.mf.sg have.vbhaver.pres see.vblex.pp prpers.prn.subj.p3.nt.sg ..sent

The output should be:
^I<num><mf><sg>$ ^have<vblex><pres>$ ^see<vblex><pp>$ ^prpers<prn><subj><p3><nt><sg>$ ^.<sent>$


4. test the whole pipeline:
     echo "I have seen it ." | lt-proc -a apertium-en-es-0.8.0/en-es.automorf.bin | ./NaiveTagger -r | ./NaiveReformatter | lt-proc -g apertium-en-es-0.8.0/es-en.autogen.bin

The output is:
I have seen it .





Task1:
======
Write a filter that reads in the output of Apertium morphological analyser and writes out either a random one (-r) or the first one (-f) of the lexical form for each surface form in a new format, respecting superblanks. 
http://wiki.apertium.org/wiki/Ideas_for_Google_Summer_of_Code/Sliding-window_part-of-speech_tagger

Example input line:
 [<em>]^I/I<num><mf><sg>/I<prn><subj><p1><mf><sg>$ ^have/have<vbhaver><inf>/have<vbhaver><pres>$[</em>]
output:
I.prn.subj.p1.mf.sg have.vbhaver.inf

Implementation:
NaiveTagger.cpp


Task2:
======
Write a converter for a roundtrip converter reading the output of NaiveTagger and regenerating the input.

Example input line:
I.prn.subj.p1.mf.sg have.vbhaver.inf
output:
^I<prn><subj><p1><mf><sg>$ ^have<vbhaver><inf>$

Implementation:
NaiveReformatter.cpp


