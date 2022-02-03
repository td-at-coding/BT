

uninstall:
	xargs rm < build/install_manifest.txt
printpdf:
	build/Graph/graph > graph.dot
	dot graph.dot -Tpdf > graph.pdf
	evince *.pdf