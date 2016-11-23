<?php
/**
 * @file
 * oAuth authentcation plugin for Deploy.
 */

/**
 * Incomplete Authenticator class that uses oAuth.
 */
class DeployAuthenticatorOAuth implements DeployAuthenticator {

  /**
   * Configuration options.
   *
   * @var array
   */
  public $config = array();

  /**
   * {@inheritdoc}
   */
  public function __construct(DeployService $service, Array $config = array()) {
    $this->service = $service;
    $this->config += array(
      'debug' => FALSE,
    );
    $this->config = array_merge($this->config, $config);
  }

  /**
   * {@inheritdoc}
   */
  public function deploy(Traversable $iterator) {

  }

  /**
   * {@inheritdoc}
   */
  public function configForm(&$form_state) {
    return array();
  }
}
