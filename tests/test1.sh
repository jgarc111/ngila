#! /bin/sh

: ${NGILA=ngila}
: ${DIFF=diff}

${NGILA} -a 2 -b 0.25 -c 0.5 ${top_srcdir}/tests/test1.fsa \
	| tail -n +2 | ${DIFF} -b -B - ${top_srcdir}/tests/test1.aln
result=$?

exit $result
