//
//  MainMenuViewController.swift
//  Quake
//
//  Created by Tom Kidd on 6/27/18.
//
//  Edited by TPX 09/11/21
//

import UIKit
import Gifu

class MainMenuViewController: UIViewController
{
    var selectedGame = QuakeGame.Quake
    var commandLine = ""
    
//tpx gif background
    let imageView = GIFImageView(frame: CGRect(x: 0, y: 0, width: 667, height: 375))
//tpx gif background end

    override func viewDidLoad()
    {
        super.viewDidLoad()
        
//tpx gif background
        //view.addSubview(imageView)
        view.insertSubview(imageView, at: 0)
//tpx gif background end
        
        let defaults = UserDefaults()
        selectedGame = QuakeGame(rawValue: defaults.integer(forKey: "selectedGame"))!
        
        //additionalCommandLine = "+map start"
        commandLine = " +map start"

        // Do any additional setup after loading the view.
    }
    
//tpx gif background
    override func viewDidAppear(_ animated: Bool)
    {
        imageView.animate(withGIFNamed: "Animation_ios")
    }
//tpx gif background end

    override func didReceiveMemoryWarning()
    {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?)
    {
        //deathmatch
        if segue.identifier == "DemoSegue"
        {
            (segue.destination as! GameViewController).additionalCommandLine = "+map dm_test"
            (segue.destination as! GameViewController).selectedGame = .Quake
        }
        else if segue.identifier == "StartGameSegue"
        {
            //(segue.destination as! GameViewController).additionalCommandLine = " +map cp_oldcity"
            (segue.destination as! GameViewController).additionalCommandLine = " +map test"
            (segue.destination as! GameViewController).selectedGame = .Quake
        }
        else if segue.identifier == "ResumeGameSegue"
        {
            (segue.destination as! GameViewController).selectedGame = selectedGame

            switch selectedGame
            {
            case .Quake:
                (segue.destination as! GameViewController).additionalCommandLine = "+map start"
            default: ()
            }
            
            (segue.destination as! GameViewController).quickLoadGame = true
        }
    }

}
