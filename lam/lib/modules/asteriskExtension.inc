<?php
/*
$Id$

  This code is part of LDAP Account Manager (http://www.sourceforge.net/projects/lam)
  Copyright (C) 2009  Pavel Pozdnyak
                2009  Roland Gruber

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/


/**
 * Description of asteriskExtension
 *
 * @author Pavel Pozdnyak
 * @author Roland Gruber
 */
class asteriskExtension extends baseModule {

	/**
	 * Returns meta data that is interpreted by parent class
	 *
	 * @return array array with meta data
	 */
	function get_metaData() {
		$return = array();
		// manages users accounts
		$return["account_types"] = array("asteriskExt");
		$return["is_base"] = true;
		// RDN attribute
		$return["RDN"] = array("cn" => "normal");
		// LDAP filter
		$return["ldap_filter"] = array('or' => "(objectClass=AsteriskExtension)"); 
		// alias name
		$return["alias"] = _("Asterisk extension");
		// module dependencies
		$return['dependencies'] = array('depends' => array(), 'conflicts' => array());
		// managed object classes
		$return['objectClasses'] = array('AsteriskExtension', 'groupOfNames');
		// managed attributes
		$return['attributes'] = array('cn', 'member', 'AstExtension', 'AstPriority',
			'AstApplication', 'AstApplicationData', 'AstContext');
		//ldap aliases
		$return['LDAPaliases'] = array('commonName' => 'cn');
		// icon
		$return['icon'] = 'asterisk.png';
		// help
		$return['help'] = array(
			'AstApplicationData' => array(
			"Headline" => _("Application data"),
			"Text" => _("This defines what application Asterisk has to start for this user (e.g. SIP/user1).")
			),			
			'AstContext' => array(
			"Headline" => _("Account context"),
			"Text" => _("The account context stores information about the dial plan.")
			),
			'AstExtension' => array(
			"Headline" => _("Extension name"),
			"Text" => _("The name of the extension (e.g. voicemail or sip).")
			),
			'AstPriority' => array(
			"Headline" => _("Priority"),
			"Text" => _("The priority is a sequence number used to order the execution of commands. Commands are executed beginning with the lowest sequence number.")
			),
			'AstApplication' => array(
			"Headline" => _("Application"),
			"Text" => _("The name of a command to execute. The available commands may be listed at the Asterisk command line by executing \"core show applications\".")
			),
			'member' => array(
			"Headline" => _("Extension owners"),
			"Text" => _("DNs of the extension owners")
			),
			'cn' => array(
			"Headline" => _("Common name"),
			"Text" => _("Common name of the Asterisk extension.")
			)
		);
		// profile options
		$return['profile_options'] = array(
			array(
				array('kind' => 'text', 'text' => _('Account context') . ":"),
				array('kind' => 'input', 'name' => 'AsteriskExtension_AstContext', 'type' => 'text', 'size' => '30', 'maxlength' => '255'),
				array('kind' => 'help', 'value' => 'AstContext')),
			array(
				array('kind' => 'text', 'text' => _('Priority') . ":"),
				array('kind' => 'input', 'name' => 'AsteriskExtension_AstPriority', 'type' => 'text', 'size' => '30', 'maxlength' => '255'),
				array('kind' => 'help', 'value' => 'AstPriority')),
			array(
				array('kind' => 'text', 'text' => _('Application') . ":"),
				array('kind' => 'input', 'name' => 'AsteriskExtension_AstApplication', 'type' => 'text', 'size' => '30', 'maxlength' => '255'),
				array('kind' => 'help', 'value' => 'AstApplication'))
		);
		$return['profile_mappings'] = array(
			'AsteriskExtension_AstContext' => 'AstContext',
			'AsteriskExtension_AstPriority' => 'AstPriority',
			'AsteriskExtension_AstApplication' => 'AstApplication',
		);
		// available PDF fields
		$return['PDF_fields'] = array(
			'AstApplicationData', 'AstContext', 'AstExtension',
			'AstPriority', 'AstApplication', 'member', 'cn'
		);
		// upload fields
		$return['upload_columns'] = array(
			array(
				'name' => 'asteriskExtension_AstExtension',
				'description' => _('Extension name'),
				'help' => 'AstExtension',
				'example' => '500',
				'required' => true
			),
			array(
				'name' => 'asteriskExtension_AstPriority',
				'description' => _('Priority'),
				'help' => 'AstPriority',
				'example' => '3',
				'required' => true
			),
			array(
				'name' => 'asteriskExtension_cn',
				'description' => _('Common name'),
				'help' => 'cn',
				'example' => _('500-1'),
				'required' => true
			),
			array(
				'name' => 'asteriskExtension_AstApplication',
				'description' => _('Application'),
				'help' => 'AstApplication',
				'example' => 'Playback',
				'required' => true
			),
			array(
				'name' => 'asteriskExtension_AstApplicationData',
				'description' => _('Application data'),
				'help' => 'AstApplicationData',
				'example' => _('test-start'),
			),
			array(
				'name' => 'asteriskExtension_AstContext',
				'description' => _('Account context'),
				'help' => 'AstContext',
				'example' => _('test'),
				'required' => true
			),
			array(
				'name' => 'asteriskExtension_member',
				'description' => _('Extension owners'),
				'help' => 'member',
				'example' => 'uid=user1,o=test;uid=user2,o=test',
				'required' => true
			),
		);
		
		return $return;
	}


	/**
	 * This function fills the error message array with messages
	 */
	function load_Messages() {		
		$this->messages['cn'][0] = array('ERROR', _('Please enter a common name.'));
		$this->messages['AstApplication'][0] = array('ERROR', _('Please enter the application.'));
		$this->messages['AstApplicationData'][0] = array('ERROR', _('Please enter the application data.'));
		$this->messages['AstContext'][0] = array('ERROR', _('Please enter the extension context.'));
		$this->messages['AstExtension'][0] = array('ERROR', _('Please enter the extension name.'));
		$this->messages['AstPriority'][0] = array('ERROR', _('Please enter the priority.'));
		$this->messages['AstExtensionAstPriority'][0] = array('ERROR', _('This pair of extension name and priority already exists.'));
		$this->messages['member'][0] = array('ERROR', _('Please add at least one member.'));
	}

	/**
	 * This function will create the meta HTML code to show a page with all attributes.
	 *
	 * @param array $_POST HTTP-POST values
	 */
	function display_html_attributes() {
		$return = array();

		$return[] = array(
			array('kind' => 'text', 'text' => _("Common name") . '*'),
			array('kind' => 'input', 'name' => 'cn', 'type' => 'text', 'size' => '30', 'maxlength' => '20', 'value' => $this->attributes['cn'][0]),
			array('kind' => 'help', 'value' => 'cn'));
		$return[] = array(
			array('kind' => 'text', 'text' => _("Account context") . '*'),
			array('kind' => 'input', 'name' => 'AstContext', 'type' => 'text', 'size' => '30', 'maxlength' => '20', 'value' => $this->attributes['AstContext'][0]),
			array('kind' => 'help', 'value' => 'AstContext'));
		$return[] = array(
			array('kind' => 'text', 'text' => _("Extension name") . '*'),
			array('kind' => 'input', 'name' => 'AstExtension', 'type' => 'text', 'size' => '30', 'maxlength' => '20', 'value' => $this->attributes['AstExtension'][0]),
			array('kind' => 'help', 'value' => 'AstExtension'));
		$return[] = array(
			array('kind' => 'text', 'text' => _("Priority") . '*'),
			array('kind' => 'input', 'name' => 'AstPriority', 'type' => 'text', 'size' => '30', 'maxlength' => '20', 'value' => $this->attributes['AstPriority'][0]),
			array('kind' => 'help', 'value' => 'AstPriority'));
		$return[] = array(
			array('kind' => 'text', 'text' => _("Application") . '*'),
			array('kind' => 'input', 'name' => 'AstApplication', 'type' => 'text', 'size' => '30', 'maxlength' => '20', 'value' => $this->attributes['AstApplication'][0]),
			array('kind' => 'help', 'value' => 'AstApplication'));
		$return[] = array(
			array('kind' => 'text', 'text' => _("Application data")),
			array('kind' => 'input', 'name' => 'AstApplicationData', 'type' => 'text', 'size' => '30', 'maxlength' => '20', 'value' => $this->attributes['AstApplicationData'][0]),
			array('kind' => 'help', 'value' => 'AstApplicationData'));
		
		$return[] = array(
			array('kind' => 'text', 'text' => _("Extension owners") . '*'),
			array('kind' => 'input', 'name' => 'form_subpage_' . get_class($this) . '_user_open', 'type' => 'submit', 'value' => _('Change')),
			array('kind' => 'help', 'value' => 'member'));
		for ($i = 0; $i < sizeof($this->attributes['member']); $i++) {
		}
		$memberPart = array();
		if (isset($this->attributes['member'])) {
			for ($i = 0; $i < sizeof($this->attributes['member']); $i++) {
				$memberPart[] = array(array('kind' => 'text', 'text' => $this->attributes['member'][$i]));
			}
		}
		$return[] = array(
			array('kind' => 'text', 'text' => ''),
			array('kind' => 'table', 'value' => $memberPart),
			array('kind' => 'text', 'text' => ''),
		);
		return $return;
	}

	/**
	 * Displays a list of possible owners of this extension.
	 *
	 * @return array list of info/error messages
	 */
	function display_html_user() {
		// load list with all users with objectClass AsteriskSIPUser
		$searchroot = $_SESSION['config']->get_Suffix('user');
		$filter = 'objectClass=AsteriskSIPUser';
		$ldapc = $_SESSION['ldap']->server();
		$attributes = array("DN", "cn");
		$res = ldap_search($ldapc,$searchroot,$filter,$attributes,0,0,0,LDAP_DEREF_NEVER);
		if (!$res) {
			return array(array("ERROR", _("Unable to load LDAP entry:") . " " .$searchroot, ldap_error($_SESSION['ldap']->server())));
		}
		$count = ldap_count_entries($ldapc, $res);
		$entry = ldap_first_entry($ldapc, $res);
		$users_dn = array();
		while ($entry) {
		$dn = ldap_get_dn($ldapc, $entry);
		if (isset($dn) && (!isset($this->attributes['member']) || !in_array($dn, $this->attributes['member']))) {
			$users_dn[] = $dn;
		}
			$entry = ldap_next_entry($ldapc, $entry);
		}
		$members = $this->attributes['member'];

		$return[] = array(
			array('kind' => 'fieldset', 'legend' => _("Extension owners"), 'value' => array(
				array(
					array('kind' => 'fieldset', 'td' => array ('valign' => 'top'), 'legend' => _("Selected users"), 'value' => array (
						array(array('kind' => 'select', 'name' => 'removeusers', 'size' => '15', 'multiple' => true, 'options' => $members)))
					),
					array('kind' => 'table', 'value' => array(
						array(array('kind' => 'input', 'type' => 'submit', 'name' => 'addusers_button', 'value' => '<=', 'td' => array('align' => 'center'))),
						array(array('kind' => 'input', 'type' => 'submit', 'name' => 'removeusers_button', 'value' => '=>', 'td' => array('align' => 'center'))),
						array(array('kind' => 'help', 'value' => 'members', 'td' => array('align' => 'center')))
					)),
					array('kind' => 'fieldset', 'td' => array('valign' => 'top'), 'legend' => _("Available users"), 'value' => array(
						array(array('kind' => 'select', 'name' => 'addusers', 'size' => '15', 'multiple' => true, 'options' => $users_dn)))
					)
				)
			))
		);
		$return[] = array(
			array('kind' => 'input', 'name' => 'form_subpage_' . get_class($this) . '_attributes_back' ,'type' => 'submit', 'value' => _('Back') ),
			array('kind' => 'text'),
			array('kind' => 'text'));
		return $return;
	}


	/**
	 * Processes user input of the user selection page.
	 * It checks if all input values are correct and updates the associated LDAP attributes.
	 *
	 * @return array list of info/error messages
	 */
	function process_user() {
		if (!isset($this->attributes['member'])) $this->attributes['member'] = array();
		if (isset($_POST['addusers']) && isset($_POST['addusers_button'])) { // Add users to list
		// Add new user
			$this->attributes['member'] = @array_merge($this->attributes['member'], $_POST['addusers']);
		}
		elseif (isset($_POST['removeusers']) && isset($_POST['removeusers_button'])) { // remove users from list
			$this->attributes['member'] = array_delete($_POST['removeusers'], $this->attributes['member']);
		}
		return array();
	}


	/**
	 * Write variables into object and do some regex checks
	 *
	 * @param array $_POST HTTP-POST values
	 */
	function process_attributes() {
		$errors = array();
		$this->attributes['AstAccountCallerID'] = array();
		$this->attributes['AstContext'] = array();
		$this->attributes['AstExtension'] = array();
		$this->attributes['AstPriority'] = array();
		$this->attributes['AstApplication'] = array();
		$this->attributes['AstApplicationData'] = array();
		$this->attributes['cn'] = array();
		if (isset($_POST['AstContext'])) {
			$this->attributes['AstContext'][0] = $_POST['AstContext'];
			if($this->attributes['AstContext'][0] == '') {
				$errors[] = $this->messages['AstContext'][0];
			}
		}
		if (isset($_POST['AstExtension'])) {
			$this->attributes['AstExtension'][0] = $_POST['AstExtension'];
			if($this->attributes['AstExtension'][0] == '') {
				$errors[] = $this->messages['AstExtension'][0];
			}
		}
		if (isset($_POST['AstPriority'])) {
			$this->attributes['AstPriority'][0] = $_POST['AstPriority'];
			if($this->attributes['AstPriority'][0] == '') {
				$errors[] = $this->messages['AstPriority'][0];
			}
		}

		if (!isset($this->orig['AstExtension']) || !isset($this->orig['AstPriority']) || ($this->orig['AstExtension'][0] != $this->attributes['AstExtension'][0])
			|| ($this->orig['AstPriority'][0] != $this->attributes['AstPriority'][0])) {			
			$searchroot = $_SESSION['config']->get_Suffix($this->get_scope());
			$filter = '(& (objectClass=AsteriskExtension) (AstExtension=' . $this->attributes['AstExtension'][0] .') (AstPriority=' . $this->attributes['AstPriority'][0] .') )';
			$ldapc = $_SESSION['ldap']->server();
			$attributes = array("DN");
			$res = ldap_search($ldapc,$searchroot,$filter,$attributes,0,0,0,LDAP_DEREF_NEVER);
			if (!$res) {
				return array(array("ERROR", _("Unable to load LDAP entry:") . " " .$searchroot, ldap_error($_SESSION['ldap']->server())));
			}
			$count = ldap_count_entries($ldapc, $res);
			if($count > 0) {
				$errors[] = $this->messages['AstExtensionAstPriority'][0];
			}
		}

		if (isset($_POST['AstApplication'])) {
			$this->attributes['AstApplication'][0] = $_POST['AstApplication'];
			if($this->attributes['AstApplication'][0] == '') {
				$errors[] = $this->messages['AstApplication'][0];
			}
		}
		if (isset($_POST['AstApplicationData'])) {
			$this->attributes['AstApplicationData'][0] = $_POST['AstApplicationData'];
		}
		if (isset($_POST['cn'])) {
			$this->attributes['cn'][0] = $_POST['cn'];
			if($this->attributes['cn'][0] == '') {
				$errors[] = $this->messages['cn'][0];
			}
		}
		if (!isset($this->attributes['member']) || (sizeof($this->attributes['member']) == 0)) {
			if (!isset($_POST['form_subpage_' . get_class($this) . '_user_open'])) {
				$errors[] = $this->messages['member'][0];
			}
		}
		return $errors;
	}




	/**
	 * In this function the LDAP account is built up.
	 *
	 * @param array $rawAccounts list of hash arrays (name => value) from user input
	 * @param array $partialAccounts list of hash arrays (name => value) which are later added to LDAP
	 * @param array $ids list of IDs for column position (e.g. "posixAccount_uid" => 5)
	 * @return array list of error messages if any
	 */
	function build_uploadAccounts($rawAccounts, $ids, &$partialAccounts) {
		$messages = array();
		for ($i = 0; $i < sizeof($rawAccounts); $i++) {
			// add object class
			if (!in_array("AsteriskExtension", $partialAccounts[$i]['objectClass'])) $partialAccounts[$i]['objectClass'][] = "AsteriskExtension";
			if (!in_array("groupOfNames", $partialAccounts[$i]['objectClass'])) $partialAccounts[$i]['objectClass'][] = "groupOfNames";
			// attributes
			$partialAccounts[$i]['cn'] = $rawAccounts[$i][$ids['asteriskExtension_cn']];
			$partialAccounts[$i]['AstExtension'] = $rawAccounts[$i][$ids['asteriskExtension_AstExtension']];
			$partialAccounts[$i]['AstPriority'] = $rawAccounts[$i][$ids['asteriskExtension_AstPriority']];
			$partialAccounts[$i]['member'] = explode(';', $rawAccounts[$i][$ids['asteriskExtension_member']]);
			if ($rawAccounts[$i][$ids['asteriskExtension_AstApplication']] != "") {
				$partialAccounts[$i]['AstApplication'] = $rawAccounts[$i][$ids['asteriskExtension_AstApplication']];
			}
			if ($rawAccounts[$i][$ids['asteriskExtension_AstApplicationData']] != "") {
				$partialAccounts[$i]['AstApplicationData'] = $rawAccounts[$i][$ids['asteriskExtension_AstApplicationData']];
			}
			if ($rawAccounts[$i][$ids['asteriskExtension_AstContext']] != "") {
				$partialAccounts[$i]['AstContext'] = $rawAccounts[$i][$ids['asteriskExtension_AstContext']];
			}
		}
		return $messages;
	}
	
	/**
	* Returns a list of PDF entries
	*/
	function get_pdfEntries() {
		$return = array();
		if (isset($this->attributes['AstContext'])) {
			$return[get_class($this) . '_AstContext'] = array('<block><key>' . _('Account context') . '</key><value>' . $this->attributes['AstContext'][0] . '</value></block>');
		}
		if (isset($this->attributes['AstApplicationData'])) {
			$return[get_class($this) . '_AstApplicationData'] = array('<block><key>' . _('Application data') . '</key><value>' . $this->attributes['AstApplicationData'][0] . '</value></block>');
		}
		if (isset($this->attributes['AstApplication'])) {
			$return[get_class($this) . '_AstApplication'] = array('<block><key>' . _('Application') . '</key><value>' . $this->attributes['AstApplication'][0] . '</value></block>');
		}
		if (isset($this->attributes['AstPriority'])) {
			$return[get_class($this) . '_AstPriority'] = array('<block><key>' . _('Priority') . '</key><value>' . $this->attributes['AstPriority'][0] . '</value></block>');
		}
		if (isset($this->attributes['AstExtension'])) {
			$return[get_class($this) . '_AstExtension'] = array('<block><key>' . _('Extension name') . '</key><value>' . $this->attributes['AstExtension'][0] . '</value></block>');
		}
		if (isset($this->attributes['member'])) {
			$return[get_class($this) . '_member'] = array('<block><key>' . _('Extension owners') . '</key><value>' . implode('; ', $this->attributes['member']) . '</value></block>');
		}
		if (isset($this->attributes['cn'])) {
			$return[get_class($this) . '_cn'] = array('<block><key>' . _('Common name') . '</key><value>' . $this->attributes['cn'][0] . '</value></block>');
		}
		return $return;
	}

}
?>