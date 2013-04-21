===================================================================
CodingChallenge for Apertium GSoC 2013, "Sliding-window Pos Tagger"
===================================================================
http://wiki.apertium.org/wiki/Ideas_for_Google_Summer_of_Code/Sliding-window_part-of-speech_tagger

Brief usage:
============
    make
    ./NaiveTagger -r < example_morph_analysis > example_morph_analysis.tagged
    ./NaiveReformatter < example_morph_analysis.tagged > example_morph_analysis.tagged.reformatted


Detailed descriptions:
======================
The coding challenge is implemented in two C++ binaries:
NaiveTagger and NaiveReformatter.

(1) NaiveTagger
The task is to write a filter that reads in the output of Apertium morphological
analyser and writes out either a random one (-r) or the first one (-f) of the 
lexical form for each surface form in a new format, respecting superblanks.

For example, we use the following command to produce a real case input:

    echo "I have seen it." | lt-proc -a en-es.automorf.bin > example_morph_analysis
    (NOTE: lttoolbox and apertium-en-es-0.8.0 data package should be installed.)

with example_morph_analysis's content being:

    ^I/I<num><mf><sg>/prpers<prn><subj><p1><mf><sg>$ ^have/have<vbhaver><inf>/have<vbhaver><pres>/have<vblex><inf>/have<vblex><pres>$ ^seen/see<vblex><pp>$ ^it/prpers<prn><subj><p3><nt><sg>/prpers<prn><obj><p3><nt><sg>$^./.<sent>$

The NaiveTagger reads example_morph_analysis and writes out one possible lexical form:

    ./NaiveTagger -r < example_morph_analysis > example_morph_analysis.tagged
    
with example_morph_analysis.tagged's content being:

    I.num.mf.sg have.vbhaver.pres see.vblex.pp prpers.prn.subj.p3.nt.sg ..sent


(2) NaiveReformatter
The task is to provide a roundtrip converter reading the output of a lexical form and regenerating the input.
The NaiveReformatter reads example_morph_analysis.tagged and outputs the morphological form:

    ./NaiveReformatter < example_morph_analysis.tagged > example_morph_analysis.tagged.reformatted
    
with example_morph_analysis.tagged.reformatted's content being:

    ^I<num><mf><sg>$ ^have<vblex><pres>$ ^see<vblex><pp>$ ^prpers<prn><subj><p3><nt><sg>$ ^.<sent>$


(3) Test both binaries in a roundtrip pipeline
The procedure is: sentence --> morphological form  ----> lexical form  ----> morphological form  ----> sentence
using the command:

    echo "I have seen it ." | lt-proc -a en-es.automorf.bin | ./NaiveTagger -r | ./NaiveReformatter | lt-proc -g es-en.autogen.bin

we get an output same as the original sentence:

    I have seen it .

