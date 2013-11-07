cs412-FPMining
==============
First run LDA on a corpus made up of titles from 5 domains' conference papers. Based on the results from LDA, a topic (representing a particular domain) is assigned to each word in each title. Then you write a frequent mining algorithm to mine frequent patterns from each topic to get meaningful phrases. The mined frequent patterns may not necessarily be *meaningful* phrases for the topic. So you will consider the question how to extract meaningful ones out of all the frequent patterns. The final goal is to output highly representative phrases for each topic.

Note
==============
Apriori is adopted for the main mining part. The algorithm works well for this problem. However, the program is somewhat slow, not because of the main algorithm but the slow function “inTrans”. The function “inTrans” checked the transition by splitting the string each time and compare with each part of a query, causing some clock cycles to finish. If anyone want to use this code, please making sure taking some time to modify this part use "tuple" or "vectors in vector" as a better data structe.

File Tree
==============
```
 [root] 	=> [code.preprocessing]		=> [generateDict] 	=> Code to generate dictionary (Run with “./generateDict”)
															=> [tokenize]	     	=> Codes to tokenize plain text (Run with “./tokenize”)

			=> [code.partitioning]			=> [lda-c-dist]			=> Codes to assign topics(given)
															=> [reorganize]		=> Codes to re-organize the terms (Run with “./reorganize”)
															=> [result]				=> Result for lda-c-dist

			=> [code.freqPatternMining]	=> Code for mining frequent patterns for each topic (Run “./fpmining #topic #minsup”. Exp:./fpmining 0 0.01)

			=> [code.cloMaxPattern]		=> Code for mining maximal/closed patterns (Run with “./closmining #topic”. Exp:./closmining 0;  “./maxmining #topic”. Exp:./maxmining 0)

			=> [code.rerankByPurity]		=> Code for re-ranking by purity of patterns (Run with “./reranking #topic”. Exp:./reranking 0)
	
			=> [patterns]							=> Result: pattern-0.txt~pattern-4.txt

			=> [max]								=> Result: max-0.txt~max-4.txt

			=> [closed]								=> Result: closed-0.txt~closed-4.txt

			=> [purity]								=> Result: purity0.txt~purity-4.txt

			=> Result: title.txt
	
			=> Result: topic-0.txt~topic-4.txt
```