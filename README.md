cs412-FPMining
==============

File Tree
==============
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