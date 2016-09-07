<?php 

function get_admin_page_settings_form(){
	$form = array();
	$form['general'] = array(
		'#type' => 'fieldset',
		'#title' => t('General Settings')
	);

	$form['general']['hook_title'] = array(
		'#title' => t('Hook name'),
		'#description' => t('Enter hook name. Example: module name where this code will paste'),
		'#type'=>'textfield',
		'#required' => FALSE
	); 

	$form['general']['admin_link'] = array(
		'#title' => t('Admin Link'),
		'#description' => t('Enter admin page link. The key of menu hook.'),
		'#type'=>'textfield',
		'#required' => TRUE
	); 

	$form['general']['admin_page_title'] = array(
		'#title' => t('Admin Page Title'),
		'#description' => t('Enter title for admin page title'),
		'#type'=>'textfield',
		'#required' => TRUE
	); 

	$form['general']['admin_page_description'] = array(
		'#title' => t('Admin Page Description'),
		'#description' => t('Enter page description'),
		'#type'=>'textfield',
	); 

	$form['general']['menu_callback_fn'] = array(
		'#title' => t('Callback Function Name'),
		'#description' => t('Enter callback function name'),
		'#type'=>'textfield',
		'#required' => TRUE
	); 

	$form['general']['page_title'] = array(
		'#title' => t('Page title'),
		'#description' => t('Enter text as page title.'),
		'#type'=>'textfield',
	); 

	$form['general']['menu_type'] = array(
		'#title' => t('Menu Type'),
		'#description' => t('Enter menu type. Example: MENU_NORMAL_ITEM, MENU_CALLBACK etc..'),
		'#type'=>'textfield',
	); 
	
	$form['general']['access_arguments'] = array(
		'#title' => t('Access Arguments'),
		'#description' => t('Enter access arguments array key with comma seperation'),
		'#type'=>'textfield',
	); 

	$form['form_elements'] = array(
		'#type' => 'fieldset',
		'#title' => t('Form Elements')	
	);

	$form['form_elements']['form_function_name'] = array(
		'#title' => t('Form function name'),
		'#description' => t('Enter form function name.'),
		'#type'=>'textfield',
		'#required' => TRUE
	);

	$form['form_elements']['form_submit_button_name'] = array(
		'#title' => t('Form submit button name'),
		'#description' => t('Enter forms submit buttons name'),
		'#type'=>'textfield',
		'#required' => TRUE
	);
	
	$form['form_elements']['textfields'] = array(
		'#title' => t('Textfields'),
		'#description' => t('Enter textfields number'),
		'#type'=>'select',
		'#options' => array('None','1','2','3','4','5','6')
	);

	$form['form_elements']['selectes'] = array(
		'#title' => t('Select Lists'),
		'#description' => t('Enter textfields number'),
		'#type'=>'select',
		'#options' => array('None','1','2','3','4','5','6')
	);

	$form['form_elements']['form_submit_button_value'] = array(
		'#title' => t('Form submit button value'),
		'#description' => t('Enter forms submit buttons value'),
		'#type'=>'textfield',
		'#required' => TRUE
	);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
	);

	$form['output_pane'] = array(
		'#type' => 'markup',
		'#prefix' => '<div><code>'.($_SESSION['rendered_code'] ? $_SESSION['rendered_code'] : ''),
		'#suffix' => '</code></div>',
	);


	return $form;
}

function kaktarua(){
	$output = '';
	$temp = drupal_get_form('get_admin_page_settings_form');
	$output .= drupal_render($temp);
	return $output;
}

function get_admin_page_settings_form_validate(&$form, &$form_state){
	/*echo '<pre>'; print_r($form_state['values']); echo '</pre>';*/
}


function get_admin_page_settings_form_submit(&$form, &$form_state){
	/*echo 'in submit';
	echo '<pre>'; print_r($form_state['values']); echo '</pre>'; */
	$fv = $form_state['values'];
	$code = ''; 

	$code .= '
		function '.$fv['hook_title'].'_menu(){<br/>
		&nbsp;&nbsp; $items[\''.trim($fv['admin_link']).'\'] = array(<br/>
			&nbsp;&nbsp;&nbsp;&nbsp;\'title\'=>t(\''.trim($fv['admin_page_title']).'\'),<br/>
			&nbsp;&nbsp;&nbsp;&nbsp;\'description\' => t(\''.trim($fv['admin_page_description']).'\'),<br/>
			&nbsp;&nbsp;&nbsp;&nbsp;\'page callback\' => \''.trim($fv['menu_callback_fn']).'\',<br/>
			&nbsp;&nbsp;&nbsp;&nbsp;\'access arguments\' => array(\''.trim($fv['access_arguments']).'\'),<br/>			
			&nbsp;&nbsp;&nbsp;&nbsp;\'type\'=>'.trim($fv['menu_type']).'<br/>
		&nbsp;&nbsp; ); <br/>
		
		&nbsp;&nbsp; return $items; <br/>
		}
	<br/>';

	$code .= '<br/>
		function '.$fv['form_function_name'].'(){<br/>
			&nbsp;&nbsp;$form = array();';
			
			if(!empty($fv['textfields'])){
				for($i = 0; $i < $fv['textfields']; $i++ ){
					$code .= '<br/>
						&nbsp;&nbsp;$form[\'\'] = array(<br/>
							&nbsp;&nbsp;&nbsp;&nbsp;\'#type\' => \'textfield\',<br/>
							&nbsp;&nbsp;&nbsp;&nbsp;\'#title\' => t(\'\'),<br/>
							&nbsp;&nbsp;&nbsp;&nbsp;\'#description\' => t(\'\'),<br/>
							&nbsp;&nbsp;&nbsp;&nbsp;\'#default_value\' => \'\',<br/>
							&nbsp;&nbsp;&nbsp;&nbsp;\'#required\' => FALSE,<br/>					
						&nbsp;&nbsp;);
					'; 	
				}
			}

			if(!empty($fv['selectes'])){
				for($i = 0; $i < $fv['selectes']; $i++ ){
					$code .= '<br/>
						&nbsp;&nbsp;$form[\'\'] = array(<br/>
							&nbsp;&nbsp;&nbsp;&nbsp;\'#type\' => \'select\',<br/>
							&nbsp;&nbsp;&nbsp;&nbsp;\'#title\' => t(\'\'),<br/>
							&nbsp;&nbsp;&nbsp;&nbsp;\'#description\' => t(\'\'),<br/>
							&nbsp;&nbsp;&nbsp;&nbsp;\'#options\' => array(),<br/>
							&nbsp;&nbsp;&nbsp;&nbsp;\'#default_value\' => \'\',<br/>
							&nbsp;&nbsp;&nbsp;&nbsp;\'#required\' => FALSE,<br/>					
						&nbsp;&nbsp;);
					'; 	
				}
			}

			$code .= '<br/>
				&nbsp;&nbsp;$form[\''.$fv['form_submit_button_name'].'\'] = array(<br/>
					&nbsp;&nbsp;&nbsp;&nbsp;\'#type\' => \'submit\',<br/>
					&nbsp;&nbsp;&nbsp;&nbsp;\'#value\' => t(\''.$fv['form_submit_button_value'].'\'),<br/>
				&nbsp;&nbsp;);
			';

			$code .= '<br/> &nbsp;&nbsp;return $form; <br/> }  
	<br/>'; 

	$code .= '<br/>
		function '.$fv['form_function_name'].'_validate($form, &$form_state){<br/>&nbsp;&nbsp;&nbsp;&nbsp; /** Validate function goes here */ <br/>}
	<br/>';	
	
	$code .= '<br/>
		function '.$fv['form_function_name'].'_submit($form, &$form_state){<br/>&nbsp;&nbsp;&nbsp;&nbsp; /** Submit function goes here */ <br/>}
	<br/>';	

	$code .= '<br/>
		function '.$fv['menu_callback_fn'].'(){<br/>
			&nbsp;&nbsp;$output = \'\';<br/>
			&nbsp;&nbsp;$temp = drupal_get_form(\''.$fv['form_function_name'].'\');<br/>
			&nbsp;&nbsp;$output .= drupal_render($temp);<br/>
			&nbsp;&nbsp;return $output;<br/>
		}
	<br/>';

	$_SESSION['rendered_code'] = $code;
	$form_state['rebuild'] = TRUE;
	/*echo '<code>'; echo $code; echo '</code>';

	exit;*/
}

