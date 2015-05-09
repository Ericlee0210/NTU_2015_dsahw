CC=g++
FNAME=heart.train
PNAME=heart.test
EPSILON=0.05
RM=rm -rf

tree_pred_func.cpp: tree $(FNAME)
	./tree $(FNAME) $(EPSILON) > $@

clean_tree_pred_func: 
	$(RM) tree_pred_func.cpp
                      
run_tree: clean_tree_pred_func predict_tree


clean:
	$(RM) tree_predictor  tree_pred_func.cpp 
