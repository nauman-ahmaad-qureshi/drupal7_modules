<?php
/**
 * @file
 * This file holds the  all the required functions other than drupal hooks 
 */
 
/**
 *  Generates the form 
 *  @param form  
 *  an assoicative array holding form elements 
 *  @param form_state 
 *  to get values from form fields.
 *  @return form 
 *  returns form
 */
function block_id_form($form, &$form_state) {
  global $base_url;	
  $form['#action'] = $base_url.'/rendered_block';	
  $form['block_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Block ID'),
    '#description' => 'Please provide the block id to render.',
  );  	
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Render',
  );
  return $form;
} 

/**
 *  The form submit handler  
 *  @param form  
 *  an assoicative array holding form elements 
 *  @param form_state 
 *  to get values from form fields.
 */
function block_id_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 *  Generates the block contents  
 *  @param block id  
 *  holds the block id  
 *  @return output 
 *  rendered html
 */
function get_block_contents($block_id) {
  $block = block_custom_block_get($block_id);
  if (is_array($block)) {
    $info = array($block['info']);
    $body = array("data" => array($block['body']));
    $output = theme('table', array('header' => $info, 'rows' => $body));
  }
  else {
    $output = "No block exists.";
  }
  return $output;
}

/**
 *  Generates the results  
 *  @return
 *  rendered html
 */
function rendered_block_results_func() {
  if (isset($_REQUEST['block_id'])) {	
    $rendered_block = get_block_contents($_REQUEST['block_id']);
  }
  else {
    $rendered_block = "Please provide block id presented in the top toolbar.";
  }
  return theme('rendered_block_results', array('results' => $rendered_block ));
}